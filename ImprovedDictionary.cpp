// File: ImprovedDictionary.cpp
// Written By: William James
// Created 10th May 2024
// Finished 16th May 2024
// Summary:
// This file implements the ImprovedDictionary class, which intends to extend the functionalities of the Dictionary class,
// to provide enhanced functionalities in interacting with a dictionary file.
//
// Input:
// - User inputs via console input for operations like choosing files, searching
//   words, listing palindromes, finding rhyming words, adding new words, and playing the
//   "Guess the Fourth Word" game.
// - File names, word inputs, and various choices are taken as string/integer parameters
//   for performing dictionary operations.
//
// Output:
// - The program outputs information to the console (cout) regarding the status of functions
//   such as file loading, word search results, palindrome lists, rhyming words, game outcomes,
//   and dictionary saving and there retrospective outputs
// - It provides feedback when no results are found for operations like listing palindromes and
//   rhyming words. Which because the file defaults to the "dictionary_2024S1.txt" file this shouldn't happen
// - Error messages are displayed for failed file operations, invalid user inputs, and duplicate
//   word entries.
//
#include "ImprovedDictionary.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <fstream>

// - menu(): Displays a menu-driven interface for interacting with the dictionary. Options
//   include choosing a file, searching for a word, listing palindromes, finding rhyming
//   words, adding a word, and playing a game.
void ImprovedDictionary::menu() {
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Choose file\n";
        std::cout << "2. Search for word\n";
        std::cout << "3. List palindromes\n";
        std::cout << "4. Rhyming words\n";
        std::cout << "5. Add a word\n"; // New option for adding a word
        std::cout << "6. Play Guess the Fourth Word\n";
        std::cout << "7. Exit program\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string filename;
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                if (loadDictionaryFromFile(filename)) {
                    std::cout << "File loaded successfully.\n";
                } else {
                    std::cout << "Failed to load file.\n";
                    std::cout << "Defaulting to dictionary_2024S1.txt\n";
                    filename = "dictionary_2024S1.txt";
                    if (loadDictionaryFromFile(filename)) {
                        std::cout << "File loaded successfully.\n";
                    }
                }
                break;
            }
            case 2: {
                std::string wordToSearch;
                Word locatedWord;
                std::cout << "Enter a word to search: ";
                std::cin >> wordToSearch;
                if (searchWordInDictionary(wordToSearch, locatedWord)) {
                    locatedWord.printDefinition();
                    std::cout << "Type: " << typeConversion(locatedWord.getType()) << "\n";
                } else {
                    std::cout << "Word not found.\n";
                }
                break;
            }
            case 3:
                listPalindromesMenu();
                break;
            case 4:
                rhymingWordsMenu();
                break;
            case 5:
                addWordMenu(); // New case for adding a word
                break;
            case 6:
                playGuessTheFourthWord();
                break;
            case 7:
                std::cout << "Thanks for using my program!\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

// - listPalindromesMenu(): Displays sub-menu options for listing palindromes within
//   specific ranges of the alphabet (A-C, D-F, etc.).
void ImprovedDictionary::listPalindromesMenu() {
    std::cout << "\nList Palindromes:\n";
    std::cout << "Choose a section of the alphabet:\n";
    std::cout << "1. A-C\n";
    std::cout << "2. D-F\n";
    std::cout << "3. G-I\n";
    std::cout << "4. J-L\n";
    std::cout << "5. M-O\n";
    std::cout << "6. P-R\n";
    std::cout << "7. S-U\n";
    std::cout << "8. V-X\n";
    std::cout << "9. Y-Z\n";
    std::cout << "Enter your choice (1-9): ";

    char choice;
    std::cin >> choice;
    choice = std::tolower(choice);

    switch (choice) {
        case '1':
            listPalindromesRange('A');
            break;
        case '2':
            listPalindromesRange('D');
            break;
        case '3':
            listPalindromesRange('G');
            break;
        case '4':
            listPalindromesRange('J');
            break;
        case '5':
            listPalindromesRange('M');
            break;
        case '6':
            listPalindromesRange('P');
            break;
        case '7':
            listPalindromesRange('S');
            break;
        case '8':
            listPalindromesRange('V');
            break;
        case '9':
            std::cout << "No Palindromes Found\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}

// - rhymingWordsMenu(): Allows users to enter a word and find rhyming words from the
//   dictionary.
void ImprovedDictionary::rhymingWordsMenu() {
    std::cout << "\nRhyming Words:\n";
    std::cout << "Enter a word to find rhyming words: ";

    std::string word;
    std::cin >> word;

    std::vector<Word> rhymingWords = findRhymingWords(word);

    if (rhymingWords.empty()) {
        std::cout << "No rhyming words found.\n";
    } else {
        for (const auto& rhymingWord : rhymingWords) {
            std::cout << rhymingWord.getName() << "\n";
        }
    }
}

// - findRhymingWords(const std::string& word): Finds and returns a vector of Word objects
//   that rhyme with the provided word.
std::vector<Word> ImprovedDictionary::findRhymingWords(const std::string& word) const {
    std::vector<Word> rhymingWords;

    // Ensure the word has at least 3 characters to find a rhyme
    if (word.length() < 3) {
        return rhymingWords;
    }

    // Extract the last three characters of the word
    std::string endSequence = word.substr(word.length() - 3);

    // Check each word in the dictionary
    for (const auto& dictWord : words) {
        std::string dictEndSequence = dictWord.getName();
        if (dictEndSequence.length() >= 3) {
            dictEndSequence = dictEndSequence.substr(dictEndSequence.length() - 3);
            if (endSequence == dictEndSequence) {
                rhymingWords.push_back(dictWord);
            }
        }
    }

    return rhymingWords;
}

// - playGuessTheFourthWord(): Implements a game where the user guesses the missing word
//   from a definition, with scoring and high score tracking.
void ImprovedDictionary::playGuessTheFourthWord() {
    std::cout << "\nWelcome to Guess the Fourth Word!\n";
    std::cout << "Current High Score: " << highScore << "\n";
    std::cout << "Instructions:\n";
    std::cout << "- You will be presented with a word and its definition.\n";
    std::cout << "- One word in the definition will be replaced by underscores.\n";
    std::cout << "- Your task is to guess the missing word.\n";
    std::cout << "- You will receive 10 points for each correct guess.\n";
    std::cout << "- The game ends when you guess incorrectly.\n";
    std::cout << "- Good luck!\n";

    std::srand(std::time(nullptr));

    while (true) {
        Word randomWord;
        do {
            randomWord = words[rand() % words.size()];
        } while (countWordsInDefinition(randomWord.getDefinition()) <= 4);

        std::string definition = randomWord.getDefinition();
        std::vector<std::string> wordsInDefinition = splitDefinitionIntoWords(definition);
        int fourthWordIndex = 3; // Assuming the fourth word index is 3 (0-indexed)

        std::string fourthWord = wordsInDefinition[fourthWordIndex];
        wordsInDefinition[fourthWordIndex] = std::string(fourthWord.size(), '_');

        std::cout << "\nWord: " << randomWord.getName() << "\n";
        std::cout << "Definition: ";
        for (const auto& word : wordsInDefinition) {
            std::cout << word << " ";
        }
        std::cout << "\n";

        std::string guess;
        std::cout << "Guess the missing word: ";
        std::cin >> guess;

        if (guess == fourthWord) {
            std::cout << "Congratulations! You guessed correctly.\n";
            highScore += 10;
        } else {
            std::cout << "Incorrect guess.\n";
            std::cout << "The correct word was: " << fourthWord << "\n";
            std::cout << "Your final score: " << highScore << "\n";
            if (highScore > 0) {
                std::cout << "New High Score!\n";
            }
            return;
        }
    }
}

// - loadDictionaryFromFile(const std::string& filename): Loads a dictionary from a file
//   into the program. This uses the function within the Dictionary.cpp file
bool ImprovedDictionary::loadDictionaryFromFile(const std::string& filename) {
    return loadFile(filename);
}

// - searchWordInDictionary(const std::string& searchWord, Word& locatedWord) const: Searches
//   for a word in the dictionary and returns its definition if found. This uses the function in the Dictionary.cpp file
bool ImprovedDictionary::searchWordInDictionary(const std::string& searchWord, Word& locatedWord) const {
    return Dictionary::searchWord(searchWord, locatedWord);
}

// - isPalindrome(const std::string& word): Checks if a given word is a palindrome.
bool ImprovedDictionary::isPalindrome(const std::string& word) {
    std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

    int i = 0, j = lowerWord.length() - 1;
    while (i < j) {
        if (lowerWord[i] != lowerWord[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}
// - listPalindromesRange(char startLetter): Lists palindromes in the dictionary that start
//   with a specified range of letters.
void ImprovedDictionary::listPalindromesRange(char startLetter) {
    std::cout << "\nPalindromes for range ";

    switch (startLetter) {
        case 'A':
            std::cout << "A-C:\n";
            break;
        case 'D':
            std::cout << "D-F:\n";
            break;
        case 'G':
            std::cout << "G-I:\n";
            break;
        case 'J':
            std::cout << "J-L:\n";
            break;
        case 'M':
            std::cout << "M-O:\n";
            break;
        case 'P':
            std::cout << "P-R:\n";
            break;
        case 'S':
            std::cout << "S-U:\n";
            break;
        case 'V':
            std::cout << "V-X:\n";
            break;
        case 'Y':
            std::cout << "Y-Z:\n";
            break;
        default:
            std::cout << "Unknown range\n";
            return;
    }

    bool foundPalindrome = false;
    for (const auto& word : words) {
        char firstChar = std::toupper(word.getName()[0]);
        if (firstChar >= startLetter && firstChar <= startLetter + 2) {
            if (isPalindrome(word.getName())) {
                std::cout << word.getName() << std::endl;
                foundPalindrome = true;
            }
        }
    }

    if (!foundPalindrome) {
        std::cout << "No palindromes found for this range.\n";
    }
}
// - addWordMenu(): Allows users to add a new word to the dictionary, including its type
//   and definition.
void ImprovedDictionary::addWordMenu() {
    std::cout << "\nAdd a Word:\n";

    std::string name, type, definition;
    std::cout << "Enter the name of the word: ";
    std::cin >> name;

    Word locatedWord;
    if (searchWordInDictionary(name, locatedWord)) {
        std::cout << "Error: Word exists, elevated privileges required to edit existing words.\n";
        return;
    }

    std::cout << "Enter the type of the word (n/noun, v/verb, adj/adjective): ";
    std::cin >> type;

    // Validate type input
    type = typeConversion(type);
    if (type == "Unknown") {
        std::cout << "Invalid word type. Please enter 'n', 'v', or 'adj'.\n";
        return;
    }

    std::cin.ignore(); // Clear input buffer

    std::cout << "Enter the definition of the word (separate multiple definitions with ; ): ";
    std::getline(std::cin, definition);

    Word newWord(name, type, definition);
    words.push_back(newWord);

    std::string filename;
    std::cout << "Enter the filename to save the dictionary: ";
    std::cin >> filename;

    if (saveDictionaryToFile(filename)) {
        std::cout << "Dictionary saved successfully.\n";
    } else {
        std::cout << "Failed to save dictionary.\n";
    }
}


// - saveDictionaryToFile(const std::string& filename) const: Saves the current state of
//   the dictionary to a file.
bool ImprovedDictionary::saveDictionaryToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << "\n";
        return false;
    }

    for (const auto& word : words) {
        file << "Type: " << word.getType() << "\n";
        file << "Definition: " << word.getDefinition() << "\n";
        file << "Word: " << word.getName() << "\n";
        file << "\n";
    }

    file.close();
    return true;
}


// - countWordsInDefinition(const std::string& definition) const: Counts the number of words
//   in a given definition string.
int ImprovedDictionary::countWordsInDefinition(const std::string& definition) const {
    int wordCount = 0;
    std::string word;
    std::istringstream stream(definition);
    while (stream >> word) {
        ++wordCount;
    }
    return wordCount;
}

// - splitDefinitionIntoWords(const std::string& definition) const: Splits a definition string
//   into individual words.
std::vector<std::string> ImprovedDictionary::splitDefinitionIntoWords(const std::string& definition) const {
    std::vector<std::string> words;
    std::string word;
    std::istringstream stream(definition);
    while (stream >> word) {
        words.push_back(word);
    }
    return words;
}


