// File: ImprovedDictionary.h
// Written By: William James
// Created 10th May 2024
// Finished 16th May 2024
// Summary:
// This file defines the ImprovedDictionary class, which is intended to improve the functionality of
// the Dictionary class by adding additional features such as menu options for palindrome
// listing, rhyming words, adding new words, and playing a word guessing game.
//
// Input:
// - The class takes input via user interaction in its menu methods to perform operations
// - File names and word inputs are taken as string parameters for loading and saving
//   dictionaries and for searching and adding words.
//
// Output:
// - The class outputs information to the console after running the functions
//   such as file loading, word search results, and game outcomes.
//
#ifndef IMPROVEDDICTIONARY_H
#define IMPROVEDDICTIONARY_H

#include "Dictionary.h"
#include <vector>
#include <string>

class ImprovedDictionary : public Dictionary { // - The class inherits from the Dictionary class and extends its functionality.
public:
    void menu(); // - Menu-driven methods allow the user to select operations interactively.
    void listPalindromesMenu();  // - Various utility methods assist in performing operations such as listing palindromes, finding rhyming words, and counting words in definitions.
    void playGuessTheFourthWord();
    bool loadDictionaryFromFile(const std::string& filename);
    bool searchWordInDictionary(const std::string& searchWord, Word& locatedWord) const;
    bool isPalindrome(const std::string& word);
    void rhymingWordsMenu();
    void addWordMenu();
    bool saveDictionaryToFile(const std::string& filename) const;
private:
    void listPalindromesRange(char startLetter);
    int countWordsInDefinition(const std::string& definition) const;
    std::vector<std::string> splitDefinitionIntoWords(const std::string& definition) const;
    std::vector<Word> findRhymingWords(const std::string& word) const; // Declaration for findRhymingWords
    int highScore = 0; // - A member variable, highScore, tracks the user's performance in the word guessing game.
};

#endif // IMPROVEDDICTIONARY_H
