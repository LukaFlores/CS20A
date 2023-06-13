/* Project 2 main
*
*	Do not submit this file
*
*/

// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif



/* Main functions
*
*	you may make any changes you want to main to test your functions.
*	We will be using our own to grade.
*
*	I'm using preprocessor directives to layout different mains to test
*	various functions.  I have several example mains.  You can insert or replace, 
*	these are here just to illustrate the technique. Cleaner than 
*	commenting/uncommenting blocks of code.
*
*/
// Choose which run to compile
#define RUN4 //RUN1 RUN2 RUN3 RUN4




 #ifdef RUN0 
// Make sure you understand the tools being used prior to building anything with them.  
// In this case, the functions to manipulate cstrings will be part of your tool set./ 
// Might be a good idea to read the section and run some simple programs from the cstring
// section of the spec.

// It is also important to get in the habit of being able to think/implement/test incrementally.
// Break up your tasks into smaller componenets and test as much as possible.  You can think of
// this as a universal law of programming: "The number of bugs grows exponentially with amount of 
// code typed between testing." 

#include"wordlist.h"
#include"studentinfo.h"

#include<iostream>
using std::cout;
using std::endl;

#include<cstring>
using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

int main() {
	//** Setup initial state 
	cout << StudentInfo::name() << endl;
	cout << StudentInfo::id() << endl;

	int max = 5, // Keep track of the max number words	
		num = 0; // Number of words we can currently store
	//Allocate rows, to point to words
	char ** testlist = new char*[max];
	// for each row, allocate space for words
	for (int i = 0; i < max; i++) {
		testlist[i] = new char[20];
	}
	
	// Initialize words
	strcpy(testlist[0], "harry");
	strcpy(testlist[1], "ron");
	strcpy(testlist[2], "hermione");
	num = 3;	// Must be consistent with intended state, 
				// e.g. there are three currently three words.

    Wordlist *wordlist = new Wordlist(5);

    wordlist->insert(0, "harry");
    wordlist->insert(0, "ron");
    wordlist->insert(0, "hermione");

    // Display Test
    std::cout << "------- Display Test --------" << std::endl;
    int retval = wordlist->display();
    std::cout << " | Expected: 3 | " << retval <<  std::endl;

    // Word Test
    std::cout << "------- Word Test --------" << std::endl;
    const char* word = wordlist->word(1);
    std::cout << " | Expected: ron | " ;
    if(word != nullptr){
        std::cout << word << std::endl;
    }

    // Size Test
    std::cout << "------- Size Test --------" << std::endl;
    std::cout << " | Expected: hermione ron harry | ";
    for (int i = 0; i < wordlist->size(); i++) {
        std::cout << wordlist->word(i) << " ";
    }
    std::cout << std::endl;

    // remove test
    std::cout << "------- remove test --------" << std::endl;
    int val = wordlist->remove("ron");
    std::cout<< " | expected: 1 | " << val << std::endl;

    // Prepend Test
    std::cout << "------- Prepend Test --------" << std::endl;
    std::cout<< " | expected: susannah mia odetta holmes dean | ";
    Wordlist wordlistPrependOne(5);
    wordlistPrependOne.insert(0,"mia");
    wordlistPrependOne.insert(0,"susannah");

    Wordlist wordlistPrependTwo(5);
    wordlistPrependTwo.insert(0,"dean");
    wordlistPrependTwo.insert(0,"holmes");
    wordlistPrependTwo.insert(0,"odetta");

    int returnValPrepend = wordlistPrependTwo.prepend(wordlistPrependOne);
    wordlistPrependTwo.display();

    // Search Test
    std::cout << "------- Search Test --------" << std::endl;

    int returnValSearch = wordlist->search("harry");
    std::cout<< " | expected: 1 | " << returnValSearch << std::endl;
    if(retval < 0) {
        std::cout << "Not Found" << std::endl;
    }

    // Sort Test
    std::cout << "------- Sort Test --------" << std::endl;

    wordlist->insert(1, "ron");

    std::cout<< " | Ascending Order" << std::endl;
    int returnValSortAsc = wordlist->sort(true);
    std::cout<< " | expected: harry hermione ron | ";
    wordlist->display();

    std::cout<< " | Descending Order" << std::endl;
    int returnValSortDsc = wordlist->sort(false);
    std::cout<< " | expected: ron hermione harry | ";
    wordlist->display();

    // Operator = Test
    std::cout << "------- Operator = Test --------" << std::endl;
    std::cout<< " | expected: ron hermione harry | ";
    Wordlist *wordlistOperator = new Wordlist(5);
    wordlistOperator = wordlist;
    wordlistOperator->display();
    wordlistOperator = wordlistOperator;

    // missyElliot Test
    std::cout << "------- missyElliot Test --------" << std::endl;
    std::cout<< " | expected: yrrah enoimreh nor | ";
    wordlist->missyElliot();
    wordlist->display();

	return 0;
}

 #elif defined RUN1  //Test constructor 


#define MAKE_MEMBERS_PUBLIC // This constant will be checked in worlist.h

#include"wordlist.h"
#include<iostream>

#include<assert.h>
using std::cout;
using std::endl;

int main() {

	Wordlist wordlist(5);



	// Assuming we made our member variables public:
	cout << "Count: " << wordlist.stored << endl; // Expect 0

	cout << "Capacity: " << wordlist.capacity << endl; // Expect 5


	return 0;
} 
#elif defined RUN2 


#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"


#include<assert.h>

// Same as above but using asserts instead of cout
//
// asserts are a way to check conditions, they will gracefully crash
// the program if the condition is not met.  
//
// This assumes you know what the end state after the function call
// should be.  Effective programmers have in mind test cases prior to 
// implmentation.  You should know what the end state should be after
// any function call.
int main() {
	Wordlist *wordlist = new Wordlist(5);

	// Assuming we made our member variables public:
	// If we failed to set our member variables correctly 
	// These assertions will fail
	assert(wordlist->stored == 0);
	assert(wordlist->capacity == 5);
	

	return 0;
}
#elif defined RUN3

#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"
#include<iostream>
using std::cout;
using std::endl;

// Test insert: Both Constructor and insert must be
// implmented prior to running this code, otherwise
// it will crash.
int main() {
	Wordlist *wordlist = new Wordlist(5);
	wordlist->insert(0, "harry");
	wordlist->insert(0, "ron");
	wordlist->insert(0, "hermione");

	// Assuming we made our member variables public:
	cout  << wordlist->words[0][2] << endl; // Expect 'r'

	cout  << wordlist->words[1] << endl; // Expect "ron"

	return 0;
}

#elif defined RUN4

#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"
#include<assert.h>
#include<cstring>

using std::strcmp;
// Test insert: same as RUN3 but with asserts. Both Constructor and insert 
// must be implmented prior to running this code, otherwise it will crash.
int main() {

	Wordlist *wordlist = new Wordlist(5);
	wordlist->insert(0, "harry");
	wordlist->insert(0, "ron");
	wordlist->insert(0, "hermione");
	
	// Assuming we made our member variables public:
	assert(wordlist->words[0][2] == 'r' ); // Individual character, can use == 

	assert(strcmp(wordlist->words[1], "ron") == 0); // cstring, must use strcmp
	
	return 0;
}
#else

// Playing with memory tracer.  For this to work you have to uncomment
// #include"debugmem.h"  in wordlist.h to have the memory tracer included
// into the project, 
//
// Assumes the Constructor, insert are correctly implemented.  Note if there is 
// undefined behavior in any of your code then all bets are off, your code 
// may "appear" correct, may crash, may generate nonesense, all are equally 
// incorrect.  
// 
#define MAKE_MEMBERS_PUBLIC

#include"debugmem.h"
#include"wordlist.h"

#include<iostream>
using std::cout;
using std::endl;

#include<assert.h>

int main() {

	Wordlist * existinglist = DEBUG_NEW Wordlist(5); // Wordlist can store 5 words


	//... Some Wordlist operations
	existinglist->insert(0, "harry");
	existinglist->insert(0, "ron");
	existinglist->insert(0, "hermione");

	GETMEMORYREPORT();
	cout << "------------------------" << endl;
	if (true) {
		Wordlist newList(*existinglist); // Copy Constructor
		GETMEMORYREPORT();

	} // Should not result in memory leaks or undefined behavior 


	delete existinglist; 
	GETMEMORYREPORT();
	cout << "------------------------" << endl;

	return 0;
}

#endif
