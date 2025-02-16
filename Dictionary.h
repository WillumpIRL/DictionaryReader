// File: Dictionary.h
// Written By: William James
// Created 6th May 2024
// Finished 16th May 2024
// Summary:
// This header file (.h) declares the Dictionary class, which provides functionality to
// load the dictionary from a file, search through the file for words, convert word types (n -> noun),
// and display a menu for interacting with the dictionary however after implementing ImprovedDictionary class it became redundant.
//
// Input:
// The functions in this class take input from the user via standard input (cin) for
// menu choices, file names, and words to search for.
// The loadFromFile function takes a filename as input to attempt to load the dictionary from said file.
// The searchWord function takes a string as input to find a matching word in the file.
// The typeConversion function takes a string as an input and converts it from (n -> noun) or (v -> verb)
//
// Output:
// The loadFromFile function returns a True or False indicating success or failure in loading the file.
// The searchWord function returns a True or False indicating if the word was found, and the locatedWord
// parameter is used to pass the Word object back.
// The typeConversion function returns a string representing the converted (n -> noun).
// The menu function displays a menu to the user and interacts with the dictionary accordingly (not used after ImprovedDictionary class).
//
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>
#include "Word.h"

class Dictionary {
protected:
    std::vector<Word> words;

public:
    bool loadFile(const std::string& filename); // The loadFromFile function reads a dictionary file (in a specific format) and populates the words vector.
    bool searchWord(const std::string& searchWord, Word& locatedWord) const; // The searchWord function searches for a word in the words vector and returns true if found.
    void menu(); // The menu function continuously displays a menu until the user chooses to exit.
    std::string typeConversion(const std::string& type) const; // The typeConversion function converts a single-character type code (n, v, adj) to a full word type.
};

#endif // DICTIONARY_H
