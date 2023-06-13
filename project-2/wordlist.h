#ifndef WORDL1ST_H
#define WORDL1ST_H
/* Wordlist header file
*
*	This file contains the class definition for the Wordlist.  
*
*	Do not make any changes to this file.
*
*	Do not submit this file
*
*	Topics: Multilevel Arrays, Pointers, Dynamic Allocation, Classes
*
*/


// Uncomment this if you want to play with memory tracer
//#include"debugmem.h" 


// All words are at most 19 characters + '\0'
const int MAX_WORD_SIZE = 20;

//	Wordlist ADT
class Wordlist {
public:
	Wordlist(const int max);

	Wordlist(const Wordlist &src);

	~Wordlist();

	int		display() const; 

	const char*	word(const int index) const;

	int		size() const;

	int		insert(const int index, const char word[]);

	int		remove(const char word[]); 

	int		prepend(const Wordlist &other);

	int		search(const char word[]) const;
	
	int		sort(const bool asc);

	int		missyElliot();

	Wordlist& operator=(const Wordlist &src);

#ifndef MAKE_MEMBERS_PUBLIC 
// If this macro is defined prior to including this header file
// it will ignore the private access specifier, and the member
// variables will be follow the above public specifier.
private:
#endif
	int		stored;		// Number of words currently stored.
	int		capacity;	// The total size of the words.
	char  **words;		// The words storing the words.
};






























































#endif
