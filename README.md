# Dictionary Program

## Overview
This program provides an interactive dictionary system that allows users to load a dictionary file, search for words, list palindromes, find rhyming words, add new words, and play a word-guessing game. The default dictionary file used is `dictionary_2024S1.txt`.

## Features
- **Load Dictionary File**: Users can load a dictionary file of their choice.
- **Search for a Word**: Retrieve definitions and word types.
- **List Palindromes**: Identify words that read the same forwards and backwards.
- **Find Rhyming Words**: Find words that rhyme with a given word.
- **Add a New Word**: Insert a new word with its type and definition.
- **Word-Guessing Game**: Play a game called "Guess the Fourth Word."

## Files and Structure
- `main.cpp`: The entry point of the program, which creates an `ImprovedDictionary` instance and runs the menu system.
- `Dictionary.h/.cpp`: Defines and implements the base `Dictionary` class, handling file loading and word searches.
- `ImprovedDictionary.h/.cpp`: Extends `Dictionary` by adding additional features like palindromes, rhyming words, and the guessing game.
- `Word.h`: Defines the `Word` class, which represents individual dictionary entries.
- `dictionary_2024S1.txt`: The default dictionary file containing word definitions and types.

## How to Use
1. Compile the program using a C++ compiler (e.g., g++):
   ```sh
   g++ main.cpp Dictionary.cpp ImprovedDictionary.cpp -o dictionary_program
   ```
2. Run the executable:
   ```sh
   ./dictionary_program
   ```
3. Follow the on-screen menu to interact with the dictionary.

OR

Download the DictionaryProgram.exe and the dictionary.txt file

## Author
Written by William James

