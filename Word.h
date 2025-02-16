// File: Word.h
// Written By: William James
// Created 5th May 2024
// Finished 16th May 2024
// Summary:
// This file defines the Word class, with its associated type
// and definition. It provides methods to get and set these attributes, as well as a
// method to print the word's details.
//
// Input:
// The class takes input via its constructor parameters for initializing the word, type,
// and definition. Setter methods allow modification of these attributes.
//
// Output:
// The class provides output to the console through the printDefinition method,
// which displays the word, its type, and its definition.
//

#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>
#include <algorithm>

class Word { // The Word class uses std::string for storing the word, type, and definition.
private:
    std::string name;
    std::string type;
    std::string definition;

public:
    explicit Word(std::string name = "", std::string type = "", std::string definition = "")
            : name(std::move(name)), type(std::move(type)), definition(std::move(definition)) {}

    std::string getName() const { return name; }
    std::string getType() const { return type; }
    std::string getDefinition() const { return definition; }

    void setName(const std::string& newName) { // Transformations are applied to the word's name to ensure uniformity (lowercase).
        name = newName;
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    }

    void setType(const std::string& newType) { type = newType; }
    void setDefinition(const std::string& newDefinition) { definition = newDefinition; }

    void printDefinition() const { // The printDefinition method outputs the word details in a formatted manner.
        std::cout << "Word: " << name << "\n";
        std::cout << "Type: " << type << "\n";
        std::cout << "Definition: " << definition << "\n";
    }
};

#endif // WORD_H
