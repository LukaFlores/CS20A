/* Wordlist source file
*
*	This file will contain the function definitions you will implement.
*	The function signitures may NOT be changed.  You may create your own
*	helper functions and include them in this file.
*
*	In addition to the specific instructions for each function, no function
*	should cause any memory leaks or alias words in any way that would result
*	in undefined behavior. 
*
*	Topics: Multilevel Pointers, Dynamic Allocation, Classes
*
*/
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++
#define _CRT_SECURE_NO_DEPRECATE
#else  // not Microsoft Visual C++, so assume UNIX interface
#endif
#define WORDLIST_H


// Do not include any other libraries
#include"wordlist.h"
#include<iostream>
#include<cstring>

using std::cout;
using std::endl;

using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

// Function: Wordlist Constructor
Wordlist::Wordlist(const int max) {
    if(max < 1){
        words = nullptr; // Set words equal to nullptr if no words 
    } else{
        stored = 0; // Set stored to zero
        capacity = max; // set capacity to max
                        //
        words = new char*[capacity]; // Allocate memory for each word
                                     
        for (int i = 0; i < capacity; i++) {
            // Allocate 20 Characters to each word as specified by spec
            *(words + i) = new char[20];
        }
    }

    return;
                                
}

// Function: Wordlist Copy Constructor
Wordlist::Wordlist(const Wordlist &src) {
    stored = src.stored; // curr stored = src.stored
    capacity = src.capacity; // curr capacity = src.capacity

    if(capacity < 1){
        words = nullptr; // if capacity is 0 all of curr words = nullptr
    } else{
        words = new char*[capacity]; // Allocate memory to new wordlist

        for (int i = 0; i < capacity; i++) {
            if(src.words[i] != nullptr){ // If Src word at i is not empty
                int lengthOfWord = std::strlen(src.words[i]); // Get Length of Current word in src
                words[i] = new char[lengthOfWord + 1]; // Allocate memory to fit string characters
                std::strcpy(words[i], src.words[i]); // Copy Charaacters from src word to current word
            }else{
                words[i] = nullptr; // If Src word is empty set current word to empty also
            }
            
        }

    }
}

// Function: Wordlist Destructor.
Wordlist::~Wordlist() {
    if(words != nullptr){ // check to see if the wordlist is nonempty
        for (int i = 0; i < capacity; i++) {
            delete[] words[i]; // Delete Each word
        }
    }
}

// Function: display
int	Wordlist::display() const {
    // If words == nullptr nothing to print
    if(words == nullptr){
        return -1;
    }


    // Print each words evenly space with " "
    for (int i = 0; i < stored; i++) {
        std::cout << words[i];

        // After Last word no space
        if(i != stored -1){
            std::cout << " ";
        }
    }

    std::cout << std::endl;

    return stored;
}

//  Function: word
const char* Wordlist::word(const int index) const {
    if(index < 0 || index > stored ){
        return nullptr; // Return nullptr if index is less than 0 or greater than stored
    }

    return words[index];

}

//  Function: size
int	Wordlist::size() const {
    return stored;
}

//  Function: insert

int	Wordlist::insert(const int index, const char word[]) {

    //** NOTE I would have seperated the code out into another function to reduce duplication, wasn't sure if it was allowed

    if (words == nullptr) {
        // Increase capacity by 1
        capacity++;

        // Create temp wordlist to store expanded words
        char** temp;
        temp = new char* [capacity];

        // Allocate memory for each word 
        for (int i = 0; i < capacity; i++)
        {
            *(temp + i) = new char[20];
        }

        // Copy words from the original wordlist to the temp wordlist
        for (int i = 0; i < capacity - 1; i++)
        {
            strcpy(temp[i], words[i]);
        }

        // Deallocate memory for the original wordlist
        for (int i = 0; i < capacity - 1; i++) {
            delete[] words[i];
        }

        // Update words pointer to point to the expanded wordlist
        words = temp;

        // Insert the new word at the front of the wordlist
        strcpy(words[0], word);
        stored++;

        return -2;

    } else if (capacity == stored) {
        // Increase capacity by 1
        capacity++;

        // Create temp wordlist to store expanded words
        char** temp;
        temp = new char* [capacity];

        // Allocate memory for each word in the temp wordlist
        for (int i = 0; i < capacity; i++)
        {
            *(temp + i) = new char[20];
        }

        // Copy words from the original wordlist to the temp wordlist
        for (int i = 0; i < capacity - 1; i++)
        {
            strcpy(temp[i], words[i]);
        }

        // Deallocate memory for the original wordlist
        for (int i = 0; i < capacity - 1; i++) {
            delete[] words[i];
        }

        // Update words pointer to point to the expanded wordlist
        words = temp;
    }

    // Determine the insert index 
    int insertIndex;
    if (index <= 0) {
        // If index is less than 0, insertIndex = front
        insertIndex = 0;

        // Shift elements to the right to make space for the new word
        for (int i = stored; i > 0; i--) {
            strcpy(words[i], words[i - 1]);
        }
    } else if (index >= stored) {
        // If index is greater than stored, insertIndex = last
        insertIndex = stored;
    } else if (index > 0 && index < stored) {
        // If 0 <= index < stored, insertIndex = index
        insertIndex = index;

        // Shift elements to the right from the given index to make space for the new word
        for (int i = stored - 1; i > index - 1; i--) {
            strcpy(words[i + 1], words[i]);
        }
    }

    // Insert the new word at the insertIndex
    strcpy(words[insertIndex], word);
    stored++;

    // Check for special cases
    if (word[0] == '\0') {
        return -1; // Return -1 if the word is empty
    } else if (capacity == stored) {
        return 1; // Return 1 if the array is full after insertion
    } else {
        return 0; // Return 0 for successful insertion
    }
}

//	Funtion: remove
int	Wordlist::remove(const char word[]) {


    if (words == nullptr) {
        return -2;
    }

            
    int removeAmount = 0;


    for (int i = 0; i < stored; i++) {
        if(std::strcmp(words[i], word) == 0){ // Compare words if equal then ...
            delete[] words[i]; // Delete word a index that were both equal
            words[i] = nullptr; // Set Word to nullptr at index
            removeAmount++; // Increase Count 
        }
    }

    int shiftIndex = 0;
    for (int i = 0; i < stored; i++) {
        if(words[i] != nullptr){ // Loop to next word
            words[shiftIndex] = words[i]; // set current word to previous word "shiftIndex"
            shiftIndex++; // Increase Shift Index by 1
        }
    }

    for (int i = shiftIndex; i < stored; i++) {
        words[i] = nullptr; // From last shiftIndex til the end of the list set all words to nullptr
    }

    stored -= removeAmount; // Remove Count from stored

    return removeAmount;
}

//  Funtion: prepend
int	Wordlist::prepend(const Wordlist &other) {

    // Check if the 'other' WordList is empty or nullptr
    if (other.words == nullptr || other.stored == 0)
        return 0; // Return 0 no words to prepend

    int totalWordsPrepended = 0;
    int newCapacity = capacity;

    // If the current capacity cannot fit both the stored wordlists, update the capacity
    if (capacity < stored + other.stored) {
        newCapacity = stored + other.stored;
    }

    char** tempWords = new char*[newCapacity];

    // Prepend words from the 'other' WordList to the temp wordlist
    for (int i = 0; i < other.stored; i++) {
        int wordLength = std::strlen(other.words[i]);
        tempWords[i] = new char[wordLength + 1];
        std::strcpy(tempWords[i], other.words[i]);
        totalWordsPrepended++;
    }

    // Copy words from the current WordList to the temp array after the prepended words
    for (int i = 0; i < stored; i++) {
        tempWords[i + other.stored] = new char[std::strlen(words[i]) + 1];
        std::strcpy(tempWords[i + other.stored], words[i]);
    }

    // Deallocate memory for the original array
    for (int i = 0; i < stored; i++) {
        delete[] words[i];
    }

    delete[] words;

    // Check for the case where the original list is nullptr
    if (words == nullptr)
        totalWordsPrepended = -1;

    // Update the capacity, words pointer, and stored count
    capacity = newCapacity;
    words = tempWords;
    stored += other.stored;

    return totalWordsPrepended;


}

// Function: search
int Wordlist::search(const char word[]) const {
    if(words == nullptr) return -1; // if word is empty or null return -1
    
    
    for (int i = 0; i < stored; i++) {
        if(std::strcmp(words[i], word) == 0){ // Compare words if equal then ...
            return i;
        }
    }

    return -2;
}

//	Funtion: sort
int	Wordlist::sort(const bool asc) {

    if(words == nullptr) return -1; // if word is empty or null return -1

    if(stored <= 1) return 1;

    bool sorted = false;
    int pass = 0;

    while (!sorted){
        sorted = true;
        pass++;

        for (int i = 0; i < stored - pass; i++) {
            if((asc && std::strcmp(words[i], words[i + 1]) < 0) || (!asc && std::strcmp(words[i], words[i + 1]) > 0 )){
                char* temp = words[i];
                words[i] = words[i + 1];
                words[i + 1] = temp;
                sorted = false;
            }
        }
    }
    return 0;
}

// Function: Assignment Operator
Wordlist& Wordlist::operator=(const Wordlist& other) {
    // Check for self-assignment
    if (this == &other)
        return *this;

    // deallocate memory for words
    if (words != nullptr) {
        for (int i = 0; i < capacity; i++) {
            delete[] words[i];
        }
        delete[] words;
    }

    // copy stored and capacity values from the other wordlist
    stored = other.stored;
    capacity = other.capacity;

    // Allocate memory for wordlist based on the capacity
    if (capacity < 1) {
        words = nullptr;
    } else {
        words = new char*[capacity];

        // Copy words from the other wordlist to the current wordlist
        for (int i = 0; i < capacity; i++) {
            if (other.words[i] != nullptr) {
                int lengthOfWord = std::strlen(other.words[i]);
                words[i] = new char[lengthOfWord + 1];
                std::strcpy(words[i], other.words[i]);
            } else {
                words[i] = nullptr;
            }
        }
    }

    // Return a reference to the updated wordlist
    return *this;
}

// Function: missyElliot
int Wordlist::missyElliot() {
    // is Wordlist empty
    if (words == nullptr)
        return -1; // Return -1 no words

    int totalSwitchedWithinWords = 0;
    // reverse each word in the wordlist
    for (int i = 0; i < stored; i++) {
        int wordLength = std::strlen(words[i]);
        for (int j = 0; j < wordLength / 2; j++) {
            // swap characters 
            char temp = words[i][j];
            words[i][j] = words[i][wordLength - j - 1];
            words[i][wordLength - j - 1] = temp;
            totalSwitchedWithinWords += 2; // increase the count of switched characters
        }
    }

    // reverse the order of words in the wordlist
    if (stored > 1) {
        for (int i = 0; i < stored / 2; i++) {
            // swap pointers to reverse the word order
            char* temp = words[i];
            words[i] = words[stored - i - 1];
            words[stored - i - 1] = temp;
        }
    }

    return totalSwitchedWithinWords; // return switches within a word
}























