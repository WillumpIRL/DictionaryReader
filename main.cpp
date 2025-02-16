// File: main.cpp
// Written By: William James
// Created 5th May 2024
// Finished 16th May 2024
// Summary:
// This file invokes ImprovedDictionary class by creating
// an instance of the class and invoking its menu function to interact with the dictionary.
//
// Input:
// The program takes input from the user when interacting with
// the dictionary menu.
//
// Output:
// The program provides output to the console based on user interaction with the menu and the functions they invoke interacting
// with the dictionary file.
//
// Comments:
// - The main function initializes an ImprovedDictionary object.
// - It then calls the menu function of the ImprovedDictionary object to display a menu
//   and interact with the dictionary.
// - The menu function allows the user to choose options such as loading a file, searching
//   for a word, listing palindromes, finding rhyming words, adding a word, playing a game,
//   and exiting the program.
// - Error handling and user prompts are included to guide the user through the program.
//
#include "ImprovedDictionary.h"

int main() { // The main function initializes an ImprovedDictionary object. Then calls the menu function
    ImprovedDictionary dictionary;

    dictionary.menu();

    return 0;
}
