// File: Dictionary.cpp
// Written By: William James
// Created 6th May 2024
// Finished 16th May 2024
// Summary:
// This file contains the implementation of the Dictionary class, which provides
// functionality to load the dictionary from an input file, search through file for words,
// convert word types (n -> noun), and display a menu for interacting with the dictionary (not used after ImprovedDictionary class)
//
// Input:
// The functions in this module take input from the user via standard input (cin) for
// menu choices, file names, and words to search for.
// The loadFromFile function takes a filename as input to load the dictionary from a file.
// The searchWord function takes a string (searchWord) as input to find a word in the dictionary.
// The typeConversion function takes a string (type) from the file as input to convert it from (n ->noun)
//
// Output:
// The loadFromFile function returns a True or False indicating if the requested file was loaded or not.
// The searchWord function returns a True or False indicating if the word was found within the file, and the locatedWord
// parameter is used to return the Word object.
// The typeConversion function returns a string representing the full word for type (n -> noun) .
// The menu function displays a menu to the user and interacts with the dictionary accordingly (Not used in program).
//
// Comments:
// - Error handling is included for invalid menu choices and file loading failures.

#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <algorithm>

bool Dictionary::loadFile(const std::string& filename) { // - The loadFromFile function reads a dictionary file (in a specific format) and populates
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return false;
    }

    words.clear();  // Clear existing words before loading new file

    std::string line;
    Word word;
    while (getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        if (line.find("Type: ") == 0) {
            word.setType(line.substr(6));
        } else if (line.find("Definition: ") == 0) {
            word.setDefinition(line.substr(12));
        } else if (line.find("Word: ") == 0) {
            word.setName(line.substr(6));
            words.push_back(word);
            word = Word();  // Reset word for next entry
        }
    }

    file.close();
    return true;
}

bool Dictionary::searchWord(const std::string& searchWord, Word& locatedWord) const { // - The searchWord function searches for a word in the words vector and returns true if found.
    std::string lowerSearchWord = searchWord;
    std::transform(lowerSearchWord.begin(), lowerSearchWord.end(), lowerSearchWord.begin(), ::tolower);

    for (const auto& word : words) {
        if (word.getName() == lowerSearchWord) {
            locatedWord = word;
            return true;
        }
    }
    return false;
}

std::string Dictionary::typeConversion(const std::string& type) const { // - The typeConversion function converts a single-character type code (n, v, adj) to a full word type.
    if (type == "n") return "Noun";
    if (type == "v") return "Verb";
    if (type == "adj") return "Adjective";
    return "Unknown";
}

void Dictionary::menu() { // - The menu function continuously displays a menu until the user chooses to exit.
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Choose file\n";
        std::cout << "2. Search for word\n";
        std::cout << "3. Exit program\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                std::string filename;
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                if (loadFile(filename)) {
                    std::cout << "File loaded successfully.\n";
                } else {
                    std::cout << "Failed to load file.\n";
                    std::cout << "Defaulting to dictionary_2024S1.txt\n";
                    filename = "dictionary_2024S1.txt";
                    if (loadFile(filename)) {
                        std::cout << "File loaded successfully.\n";
                    }
                }
                break;
            }
            case 2: {
                std::string wordToLocate;
                Word locatedWord;
                std::cout << "Enter a word to search: ";
                std::cin >> wordToLocate;
                std::transform(wordToLocate.begin(), wordToLocate.end(), wordToLocate.begin(), ::tolower);

                if (searchWord(wordToLocate, locatedWord)) {
                    locatedWord.printDefinition();
                    std::cout << "Type: " << typeConversion(locatedWord.getType()) << "\n";
                } else {
                    std::cout << "Word not found.\n";
                }
                break;
            }
            case 3:
                std::cout << "Thanks for using my program!\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
