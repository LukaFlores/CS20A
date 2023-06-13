#ifndef PROJECT2_WLTEST_H
#define PROJECT2_WLTEST_H
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif
#include<iostream>
#include <fstream>
#include <sstream> 
#include<string>
#include<iterator>
#include<vector>
#include<assert.h>
#include<cstring>
#include<algorithm>
using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

#ifdef _MSC_VER 
#define __func__ __FUNCTION__
#endif


// Comment this out if not using
#include"debugmem.h"

// Blank out macros if debugmem.h is not included
#ifndef DEBUG_NEW
#define DEBUG_NEW new 
#endif
#ifndef RESET()
#define RESET()
#endif
#ifndef GETMEMORYREPORT()
#define GETMEMORYREPORT()
#endif
#ifndef SIZE()
#define SIZE() 0
#endif

#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"

#include<assert.h>
#include<exception>
#include<functional>


int runTest(std::function<int(int)> test, int testNum) {
	int retval = 0;
	try {
		retval = test(testNum);
	}
	catch (const std::runtime_error& re) {
		std::cerr << "Runtime error: " << re.what() << std::endl;
		retval = 1;
	}
	catch (const std::exception& ex) {
		std::cerr << "Error occurred: " << ex.what() << std::endl;
		retval = 1;
	}
	catch (...) {
		std::cerr << "Unknown failure occurred. Possible memory corruption" << std::endl;
		retval = 1;;
	}
	return retval;
}

//**********************************************************************
//Test implementations based on
//WordLists designed with the back
//element being the Front.
namespace BackRelative {
	//Empty
}
//**********************************************************************

//Test implementations based on
//WordLists designed with the zeroth
//element being the Front.
namespace ZeroRelative {
	
	int test_ctor(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup/Test 
			Wordlist *wl = new Wordlist(0);

			// Verify Results
			assert(wl->capacity == 0);
			assert(wl->stored == 0);
			assert(wl->words == nullptr);
			break;
		}
		case 1: {
			// Setup/Test
			Wordlist *wl = new Wordlist(-99);

			// Verify Results
			assert(wl->capacity == 0);
			assert(wl->stored == 0);
			assert(wl->words == nullptr);
		
			break;
		}
		case 2: {
			// Setup/Test
			Wordlist *wl = new Wordlist(10);

			// Verify Results
			assert(wl->capacity == 10);
			assert(wl->stored == 0);
			assert(wl->words != nullptr);
			if (wl->words != nullptr) {
				for (int i = 0; i < 10; i++)
					assert(wl->words[i] != nullptr);
			}
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;

		}
		return 0;
	}


	int test_display(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup Initial State
			int max = 5, 
				num = 0; 
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);

			// Inject initial state into object being tested
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			std::string test_string1("Tom Dick Mary\n"); //Without lagging space
			std::stringstream buffer(test_string1);
			std::vector<std::string> test_vector{ std::istream_iterator<std::string>(buffer), std::istream_iterator<std::string>() };
			buffer.str("");

			std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

			// Invoke
			int retval = wl->display();

			// Hijack the buffer
			std::cout.rdbuf(old);
			std::string text = buffer.str();
			std::vector<std::string> ret{ std::istream_iterator<std::string>(buffer),
				std::istream_iterator<std::string>() };

			//Verify
			assert(retval == 3);
			assert(text.length() == test_string1.length());
			assert(text == test_string1);

			break;
		}
		case 1: {
			//Setup
			Wordlist *wl = new Wordlist(0);
			//Inject
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			std::string test_string1(""); //Without lagging space
			std::stringstream buffer(test_string1);
			std::vector<std::string> test_vector{ std::istream_iterator<std::string>(buffer), std::istream_iterator<std::string>() };
			buffer.str("");

			std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

			// Invoke 
			int retval = wl->display();

			// Hijack the buffer
			std::cout.rdbuf(old);
			std::string text = buffer.str();
			std::vector<std::string> ret{ std::istream_iterator<std::string>(buffer),
				std::istream_iterator<std::string>() };

			// Verify
			assert(retval == -1);
			assert(text.length() == test_string1.length());
			assert(text == test_string1);
			break;
		}
		case 2: {
			// Setup Initial State
			int max = 5, 
				num = 0; 
			char ** testlist = new char*[max];
	
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State 
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			std::string test_string1("Tom Dick Mary\n"); //Without lagging space
			std::stringstream buffer(test_string1);
			std::vector<std::string> test_vector{ std::istream_iterator<std::string>(buffer), std::istream_iterator<std::string>() };
			buffer.str("");
			std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

			// Invoke 
			int retval = wl->display();

			// Hijack the buffer
			std::cout.rdbuf(old);
			std::string text = buffer.str();
			std::vector<std::string> ret{ std::istream_iterator<std::string>(buffer),
				std::istream_iterator<std::string>() };

			std::stringstream ss(text);
			std::istream_iterator<std::string> begin(ss);
			std::istream_iterator<std::string> end;
			std::vector<std::string> vstrings(begin, end);
			std::cout << text << std::endl;

			// Verify
			for (int i = 0; i < std::min(vstrings.size(), test_vector.size()); i++) {
				assert(vstrings[i] == test_vector[i]);
			}
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_word(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup Initial State
			int max = 5, 
				num = 0; 

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(strcmp("Tom", wl->word(0))==0);
			assert(strcmp("Dick", wl->word(1)) == 0);
			assert(strcmp("Mary", wl->word(2)) == 0);
			break;
		}
		case 1: {
			// Setup
			int max = 5, 
				num = 0; 

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->word(100)==nullptr);
		
			break;
		}
		case 2: {
			// Setup
			int max = 5, 
				num = 0; 
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->word(-1) == nullptr);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_size(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			Wordlist *wl = new Wordlist(0);

			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke and Verify Results
			assert(wl->size() == 0);
			break;
		}
		case 1: {
			// Setup 
			int max = 5,
				num = 0; 

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->size() == num);

			break;
		}
	
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_insert(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: { 
			// Setup
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke and Verify Results
			assert(wl->insert(0,"Tom")==-2);
			break;
		}
		case 1: {
			// Setup 
			Wordlist *wl = new Wordlist(0);
			char *word = new char[4];
			strcpy(word, "Tom");
			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke Function to be Verified
			wl->insert(0, "Tom");

			// Verify Results
			assert(wl->capacity == 1);
			assert(wl->stored == 1);
			assert(wl->words != nullptr);
			assert(wl->words[0] != word);
			if(wl->words != nullptr)
				assert(strcmp("Tom", wl->words[0]) == 0);
			break;
		}
		case 2: { 
			// Setup 
			Wordlist *wl = new Wordlist(0);

			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke and Verify Results
			assert(wl->insert(0, "") == -2);

			break;
		}
		case 3: {
			// Setup 
			int max = 5, 
				num = 0; 
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->insert(0, "") == -1);

			break;
		}
		case 4: {
			// Setup 
			int max = 3, 
				num = 0; 
			char ** testlist = new char*[max];

			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;
			// Invoke and Verify Results
			assert(wl->insert(0, "Jane") == 1);

			break;
		}
		case 5: {
			// Setup 
			char *word = new char[5];
			strcpy(word, "Jane");

			int max = 3, 
				num = 0; 
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke Function to be Verified
			wl->insert(0, word);

			// Verify Results
			assert(wl->capacity == 4);
			assert(wl->stored == 4);
			assert(wl->words != nullptr);
			assert(wl->words[0] != nullptr);
			assert(wl->words[0] != word);
			if (wl->words != nullptr && wl->words[0] != nullptr)
				assert(strcmp("Jane", wl->words[0]) == 0);

			break;
		}
		case 6: {
			// Setup 
			int max = 5,
				num = 0; 

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->insert(0, "Jane") == 0);

			break;
		}
		case 7: {
			// Setup 
			char *word = new char[4];
			strcpy(word, "Jane");
			int max = 5, 
				num = 0; 
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke Function to be Verified
			wl->insert(0, word);

			// Verify Results
			assert(wl->capacity == 5);
			assert(wl->stored == 4);
			assert(wl->words != nullptr);
			assert(wl->words[0] != nullptr);
			assert(wl->words[0] != word);
			if (wl->words != nullptr && wl->words[0] != nullptr)
				assert(strcmp(word, wl->words[0]) == 0);

			break;
		}
		case 8: {
			// Setup
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke and Verify Results
			assert(wl->insert(-1, "Tom") == -2);
			assert(wl->stored == 1);
			assert(wl->capacity == 1);
			assert(strcmp(wl->words[0], "Tom") == 0);
			break;
		}
		case 9: {
			// Setup
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke and Verify Results
			assert(wl->insert(-1, "Tom") == -2);
			assert(wl->stored == 1);
			assert(wl->capacity == 1);
			assert(strcmp(wl->words[0], "Tom") == 0);
			break;
		}
		case 10: {
			// Setup 
			char *word = new char[4];
			strcpy(word, "Jane");
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke Function to be Verified
			wl->insert(-1, word);

			// Verify Results
			assert(wl->capacity == 5);
			assert(wl->stored == 4);
			assert(wl->words != nullptr);
			assert(wl->words[0] != nullptr);
			assert(wl->words[0] != word);
			if (wl->words != nullptr && wl->words[0] != nullptr)
				assert(strcmp(word, wl->words[0]) == 0);
			if (wl->words != nullptr && wl->words[1] != nullptr)
				assert(strcmp("Tom", wl->words[1]) == 0);
			if (wl->words != nullptr && wl->words[2] != nullptr)
				assert(strcmp("Dick", wl->words[2]) == 0);
			if (wl->words != nullptr && wl->words[3] != nullptr)
				assert(strcmp("Mary", wl->words[3]) == 0);

			break;
		}
		case 11: {
			// Setup 
			char *word = new char[4];
			strcpy(word, "Jane");
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke Function to be Verified
			wl->insert(4, word);

			// Verify Results
			assert(wl->capacity == 5);
			assert(wl->stored == 4);
			assert(wl->words != nullptr);
			assert(wl->words[3] != nullptr);
			assert(wl->words[3] != word);
			if (wl->words != nullptr && wl->words[3] != nullptr)
				assert(strcmp(word, wl->words[3]) == 0);
			if (wl->words != nullptr && wl->words[0] != nullptr)
				assert(strcmp("Tom", wl->words[0]) == 0);
			if (wl->words != nullptr && wl->words[1] != nullptr)
				assert(strcmp("Dick", wl->words[1]) == 0);
			if (wl->words != nullptr && wl->words[2] != nullptr)
				assert(strcmp("Mary", wl->words[2]) == 0);

			break;
		}
		case 12: {
			// Setup 
			char *word = new char[4];
			strcpy(word, "Jane");
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke Function to be Verified
			int retval = wl->insert(1, word);

			// Verify Results
			assert(retval == 0);
			assert(wl->capacity == 5);
			assert(wl->stored == 4);
			assert(wl->words != nullptr);
			assert(wl->words[0] != nullptr);
			assert(wl->words[0] != word);
			if (wl->words != nullptr && wl->words[1] != nullptr)
				assert(strcmp(word, wl->words[1]) == 0);
			if (wl->words != nullptr && wl->words[0] != nullptr)
				assert(strcmp("Tom", wl->words[0]) == 0);
			if (wl->words != nullptr && wl->words[2] != nullptr)
				assert(strcmp("Dick", wl->words[2]) == 0);
			if (wl->words != nullptr && wl->words[3] != nullptr)
				assert(strcmp("Mary", wl->words[3]) == 0);

			break;
		}
		case 13: {
			// Setup 
			char *word = new char[4];
			strcpy(word, "Jane");
			int max = 3,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke Function to be Verified
			int retval = wl->insert(1, word);

			// Verify Results
			assert(retval == 1);
			assert(wl->capacity == 4);
			assert(wl->stored == 4);
			assert(wl->words != nullptr);
			assert(wl->words[0] != nullptr);
			assert(wl->words[0] != word);
			if (wl->words != nullptr && wl->words[1] != nullptr)
				assert(strcmp(word, wl->words[1]) == 0);
			if (wl->words != nullptr && wl->words[0] != nullptr)
				assert(strcmp("Tom", wl->words[0]) == 0);
			if (wl->words != nullptr && wl->words[2] != nullptr)
				assert(strcmp("Dick", wl->words[2]) == 0);
			if (wl->words != nullptr && wl->words[3] != nullptr)
				assert(strcmp("Mary", wl->words[3]) == 0);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}
	int test_remove(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);

		switch (testNum) {
		case 0: { 

			// Setup 
			Wordlist *wl = new Wordlist(0);

			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke and Verify Results
			assert(wl->remove("Tom") == -2);

			break;
		}
		case 1: {
			// Setup 
			char *word = new char[4];
			strcpy(word, "");

			int max = 10, 
				num = 0; 

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			strcpy(testlist[4], "Kaylee");
			strcpy(testlist[5], "River");
			strcpy(testlist[6], "Book");
			strcpy(testlist[7], "Wash");
			num = 8;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->remove(word)==0);
	
			break;
		}
		case 2: {

			// Setup 
			int max = 10, 
				num = 0; 

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			strcpy(testlist[4], "Kaylee");
			strcpy(testlist[5], "River");
			strcpy(testlist[6], "Book");
			strcpy(testlist[7], "Wash");
			num = 8;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;
			// Invoke and Verify Results
			assert(wl->remove("Wash") == 2);

			break;
		}
		case 3: { 
			// Setup 
			int max = 10, 
				num = 0; 

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			strcpy(testlist[4], "Kaylee");
			strcpy(testlist[5], "River");
			strcpy(testlist[6], "Book");
			strcpy(testlist[7], "Wash");
			num = 8;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke Function to be Verified
			wl->remove("Wash");

			// Verify Results
			assert(wl->stored == 6);
			assert(strcmp("Mal", wl->words[0]) == 0);
			assert(strcmp("Inara", wl->words[1]) == 0);
			assert(strcmp("Jayne", wl->words[2]) == 0);
			assert(strcmp("Kaylee", wl->words[3]) == 0);
			assert(strcmp("River", wl->words[4]) == 0);
			assert(strcmp("Book", wl->words[5]) == 0);

			break;
		}
		case 4: { 
			// Setup 
			int max = 10, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			strcpy(testlist[4], "Kaylee");
			strcpy(testlist[5], "River");
			strcpy(testlist[6], "Book");
			strcpy(testlist[7], "Wash");
			num = 8;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->remove("Operative") == 0);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_prepend(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			int max = 10, 
				num = 0; 
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for First Wordlist
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			Wordlist *other = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			other->capacity = 0;
			other->stored = 0;
			other->words = nullptr;

			// Invoke and Verify Results
			assert(wl->prepend(*other) == 0);
			break;
		}
		case 1: {
			// Setup 
			int max = 10, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for First Wordlist
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			Wordlist *other = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			other->capacity = max;
			other->stored = num;
			other->words = testlist;

			// Invoke and Verify Results
			assert(wl->prepend(*other) == -1);

			break;
		}
		case 2: { 
			// Setup 
			int max = 10, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for First Wordlist
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			Wordlist *other = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			other->capacity = max;
			other->stored = num;
			other->words = testlist;

			// Invoke Function to be Verified
			wl->prepend(*other);

			// Verify
			assert(wl->stored == 4);
			assert(wl->capacity == 4);
			assert(wl->words != nullptr);
			for (int i = 0; i < wl->stored; i++) {
				assert(wl->words[i] != nullptr);
				if (wl->words[i] == nullptr)
					return -1;
			}
		
			if (wl->words != nullptr) {
				//Aliasing
				assert( (wl->words != other->words) );
				for (int i = 0; i < wl->capacity; i++) {
					for (int j = 0; j < other->capacity; j++) {
						assert( (wl->words[i] != other->words[j]) );
					}
				}

				assert(strcmp(wl->words[0], other->words[0]) == 0);
				assert(strcmp(wl->words[1], other->words[1]) == 0);
				assert(strcmp(wl->words[2], other->words[2]) == 0);
				assert(strcmp(wl->words[3], other->words[3]) == 0);
			}


			break;
		}
		case 3: {
			// Setup 
			int max = 10, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for First Wordlist
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;


			int max2 = 10, // Keep track of the max number words	
				num2 = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for words
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist2[0], "Bob");
			strcpy(testlist2[1], "Betty");
			strcpy(testlist2[2], "Barry");
			strcpy(testlist2[3], "Ben");
			num2 = 4;

			Wordlist *other = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			other->capacity = max2;
			other->stored = num2;
			other->words = testlist2;

			// Invoke and Verify Results
			assert(wl->prepend(*other) == 4);

			break;
		}
		case 4: {
			// Setup 
			int max = 10, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for First Wordlist
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;


			int max2 = 10, // Keep track of the max number words	
				num2 = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for words
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist2[0], "Bob");
			strcpy(testlist2[1], "Betty");
			strcpy(testlist2[2], "Barry");
			strcpy(testlist2[3], "Ben");
			num2 = 4;

			Wordlist *other = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			other->capacity = max2;
			other->stored = num2;
			other->words = testlist2;

			// Invoke Function to be Verified
			wl->prepend(*other);

			// Verify Results
			assert(wl->stored == 8);
			assert(wl->capacity == 10);
			assert(wl->words != nullptr);

			for (int i = 0; i < wl->stored; i++) {
				assert(wl->words[i] != nullptr);
				if (wl->words[i] == nullptr)
					return -1;
			}
			if (wl->words != nullptr) {
				assert(wl->words != other->words);
				for (int i = 0; i < wl->capacity; i++){
					for (int j = 0; j < other->capacity; j++) {
						assert(wl->words[i] != other->words[j]);
					}
				}

				assert(strcmp(wl->words[0], other->words[0]) == 0);
				assert(strcmp(wl->words[1], other->words[1]) == 0);
				assert(strcmp(wl->words[2], other->words[2]) == 0);
				assert(strcmp(wl->words[3], other->words[3]) == 0);
			
			}
			break;
		}
		case 5: {
			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for First Wordlist
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;


			int max2 = 10, // Keep track of the max number words	
				num2 = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for words
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist2[0], "Bob");
			strcpy(testlist2[1], "Betty");
			strcpy(testlist2[2], "Barry");
			strcpy(testlist2[3], "Ben");
			num2 = 4;

			Wordlist *other = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			other->capacity = max2;
			other->stored = num2;
			other->words = testlist2;

			// Invoke and Verify Results
			assert( (wl->prepend(*other) == 4) );
			break;
		}
		case 6: {
			// Setup
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for First Wordlist
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			int max2 = 10, // Keep track of the max number words	
				num2 = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for words
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist2[0], "Bob");
			strcpy(testlist2[1], "Betty");
			strcpy(testlist2[2], "Barry");
			strcpy(testlist2[3], "Ben");
			num2 = 4;

			Wordlist *other = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			other->capacity = max2;
			other->stored = num2;
			other->words = testlist2;

			// Invoke Function to be Verified
			wl->prepend(*other);

			// Verify Results
			assert(wl->stored == 8);
			assert(wl->capacity == 8);
			assert(wl->words != nullptr);

			for (int i = 0; i < wl->stored; i++) {
				assert(wl->words[i] != nullptr);
				if (wl->words[i] == nullptr)
					return -1;
			}
			if (wl->words != nullptr) {
				assert(wl->words != other->words);
				for (int i = 0; i < wl->stored; i++) {
					for (int j = 0; j < other->stored; j++) {
						assert( (wl->words[i] != other->words[j]) );
					}
				}

				assert(strcmp(wl->words[0], other->words[0]) == 0);
				assert(strcmp(wl->words[1], other->words[1]) == 0);
				assert(strcmp(wl->words[2], other->words[2]) == 0);
				assert(strcmp(wl->words[3], other->words[3]) == 0);
			}
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}
	int test_search(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke and Verify Results
			assert(wl->search("Bob")==-1);


			break;
		}
		case 1: { 
			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->search("Bob") == -2);
			//assert(wl->capacity == max);

			break;
		}
		case 2: {
			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->search("Mal") == 0);

			break;
		}
		case 3: { 
			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->search("Jayne") == 3);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_sort(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);

		switch (testNum) {
		case 0: {
			// Setup 

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke and Verify Results
			assert(wl->sort(true) == -1);
			break;
		}
		case 1: {
			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			num = 1;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->sort(true) == 1);

			break;
		}
		case 2: { 
			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Richard");
			strcpy(testlist[1], "Door");
			strcpy(testlist[2], "Carabas");
			strcpy(testlist[3], "Islington");
			strcpy(testlist[3], "Abbot");
			num = 5;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->sort(true) == 0);

			break;
		}
		case 3: { 

			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Richard");
			strcpy(testlist[1], "Islington");
			strcpy(testlist[2], "Carabas");
			strcpy(testlist[3], "Door");
			strcpy(testlist[4], "Abbot");
			num = 5;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke Function to be Verified
			wl->sort(false);
			wl->display();
			// Verify Results
			assert(wl->words != nullptr);
			for (int i = 0; i < wl->stored; i++) {
				assert(wl->words[i] != nullptr);
				if (wl->words[i] == nullptr)
					return -1;
			}
			if (wl->words != nullptr) {
	
				assert(strcmp(wl->words[0], "Abbot") == 0);
				assert(strcmp(wl->words[1], "Carabas") == 0);
				assert(strcmp(wl->words[2], "Door") == 0);
				assert(strcmp(wl->words[3], "Islington") == 0);
				assert(strcmp(wl->words[4], "Richard") == 0);
			}
			break;
		}
		case 4: {

			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Richard");
			strcpy(testlist[1], "Islington");
			strcpy(testlist[2], "Carabas");
			strcpy(testlist[3], "Door");
			strcpy(testlist[4], "Abbot");
			num = 5;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke Function to be Verified
			wl->sort(true);

			// Verify Results
			assert(wl->words != nullptr);
			for (int i = 0; i < wl->stored; i++) {
				assert(wl->words[i] != nullptr);
				if (wl->words[i] == nullptr)
					return -1;
			}
			if (wl->words != nullptr) {

				assert(strcmp(wl->words[4], "Abbot") == 0);
				assert(strcmp(wl->words[3], "Carabas") == 0);
				assert(strcmp(wl->words[2], "Door") == 0);
				assert(strcmp(wl->words[1], "Islington") == 0);
				assert(strcmp(wl->words[0], "Richard") == 0);
			}
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_copyctor(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke Function to be Verified
			Wordlist *copy = new Wordlist(*wl);

			// Verify Results
			assert(copy->capacity==0);
			assert(copy->stored == 0);
			assert(copy->words == nullptr);

			break;
		}
		case 1: { 
			// Setup 
			int max = 10, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;


			Wordlist *other = new Wordlist(0);
			// Inject Initial State
			other->capacity = max;
			other->stored = num;
			other->words = testlist;


			// Invoke Function to be Verified
			Wordlist *wl = new Wordlist(*other);

			// Verify Results
			assert(wl->stored == other->stored);
			assert(wl->capacity == other->capacity);
			assert(wl->words != nullptr);
			for (int i = 0; i < wl->stored; i++) {
				assert(wl->words[i] != nullptr);
				if (wl->words[i] == nullptr)
					return -1;
			}
			if (wl->words != nullptr) {
				assert(wl->words != other->words);
				for (int i = 0; i < wl->capacity; i++) {
					for (int j = 0; j < other->capacity; j++) {
						assert(wl->words[i] != other->words[j]);
					}
				}
				assert(strcmp(wl->words[0], other->words[0]) == 0);
				assert(strcmp(wl->words[1], other->words[1]) == 0);
				assert(strcmp(wl->words[2], other->words[2]) == 0);
				assert(strcmp(wl->words[3], other->words[3]) == 0);
			}
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_assignOper(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for First Wordlist
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			Wordlist *copy = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			copy->capacity = 0;
			copy->stored = 0;
			copy->words = nullptr;

			// Invoke Function to be Verified
			*copy = *wl;


			// Verify Results
			assert(copy->capacity == 0);
			assert(copy->stored == 0);
			assert(copy->words == nullptr);


			break;
		}
		case 1: {
			// Setup 
			int max = 10, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;


			Wordlist *other = new Wordlist(0);
			// Inject Initial State for First Wordlist
			other->capacity = max;
			other->stored = num;
			other->words = testlist;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke Function to be Verified
			*wl = *other;

			// Verify Results
			assert(wl->stored == other->stored);
			assert(wl->capacity == other->capacity);
			assert(wl->words != nullptr);
			for (int i = 0; i < wl->stored; i++) {
				assert(wl->words[i] != nullptr);
				if (wl->words[i] == nullptr)
					return -1;
			}
			if (wl->words != nullptr) {
				assert(wl->words != other->words);
				for (int i = 0; i < wl->capacity; i++) {
					for (int j = 0; j < other->capacity; j++) {
						assert(wl->words[i] != other->words[j]);
					}
				}
				assert(strcmp(wl->words[0], other->words[0]) == 0);
				assert(strcmp(wl->words[1], other->words[1]) == 0);
				assert(strcmp(wl->words[2], other->words[2]) == 0);
				assert(strcmp(wl->words[3], other->words[3]) == 0);
			}

			break;
		}
		case 2: {
			// Setup 
			int max = 10, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;


			Wordlist *other = new Wordlist(0);
			// Inject Initial State for First Wordlist
			other->capacity = max;
			other->stored = num;
			other->words = testlist;

			int max2 = 5, // Keep track of the max number words	
				num2 = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for words
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist2[0], "Richard");
			strcpy(testlist2[1], "Islington");
			strcpy(testlist2[2], "Carabas");
			strcpy(testlist2[3], "Door");
			strcpy(testlist2[4], "Abbot");
			num2 = 5;


			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			wl->capacity = max2;
			wl->stored = num2;
			wl->words = testlist2;

			// Invoke Function to be Verified
			*wl = *other;

			// Verify Results
			assert(wl->stored == other->stored);
			assert(wl->capacity == other->capacity);
			assert(wl->words != nullptr);
			for (int i = 0; i < wl->stored; i++) {
				assert(wl->words[i] != nullptr);
				if (wl->words[i] == nullptr)
					return -1;
			}
			if (wl->words != nullptr) {
				assert(wl->words != other->words);
				for (int i = 0; i < wl->capacity; i++) {
					for (int j = 0; j < other->capacity; j++) {
						assert(wl->words[i] != other->words[j]);
					}
				}
				assert(strcmp(wl->words[0], other->words[0]) == 0);
				assert(strcmp(wl->words[1], other->words[1]) == 0);
				assert(strcmp(wl->words[2], other->words[2]) == 0);
				assert(strcmp(wl->words[3], other->words[3]) == 0);
			}

			break;
		}
		case 3: {
			// Setup 
			Wordlist *other = new Wordlist(0);
			// Inject Initial State for First Wordlist
			other->capacity = 0;
			other->stored = 0;
			other->words = nullptr;

			Wordlist *wl = new Wordlist(0);

			RESET();
			int max2 = 5, // Keep track of the max number words	
				num2 = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist2 = DEBUG_NEW char*[max2];
			// for each row, allocate space for words
			for (int i = 0; i < max2; i++) {
				testlist2[i] = DEBUG_NEW char[20];
			}

			// Initialize words
			strcpy(testlist2[0], "Richard");
			strcpy(testlist2[1], "Islington");
			strcpy(testlist2[2], "Carabas");
			strcpy(testlist2[3], "Door");
			strcpy(testlist2[4], "Abbot");
			num2 = 5;
			// Inject Initial State for Second Wordlist
			wl->capacity = max2;
			wl->stored = num2;
			wl->words = testlist2;

			// Invoke Function to be Verified
			*wl = *other;

			// Verify Results
			assert(wl->capacity == 0);
			assert(wl->stored == 0);
			assert(wl->words == nullptr);

			if (SIZE() != 0) {
				std::cerr << "Assign Op: Memory Leak detected" << std::endl;
			}
			assert(SIZE() == 0);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_dtor(int testNum) {
		std::cout << std::endl << std::endl; 
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			RESET();
			int max2 = 5, // Keep track of the max number words	
				num2 = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist2 = DEBUG_NEW char*[max2];
			// for each row, allocate space for words
			for (int i = 0; i < max2; i++) {
				testlist2[i] = DEBUG_NEW char[20];
			}

			// Initialize words
			strcpy(testlist2[0], "Richard");
			strcpy(testlist2[1], "Islington");
			strcpy(testlist2[2], "Carabas");
			strcpy(testlist2[3], "Door");
			strcpy(testlist2[4], "Abbot");
			num2 = 5;

			{
				Wordlist wl(0);
				// Inject Initial State
				wl.capacity = max2;
				wl.stored = num2;
				wl.words = testlist2;

			} // Invoke Function to be Verified

			// Verify Results
			//GETMEMORYREPORT();
			if (SIZE() != 0) {
				std::cerr << "Destructor: Memory Leak detected" << std::endl;
			}
			assert(SIZE() == 0);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_missy(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);

		switch (testNum) {
		case 0: {
			// Setup 

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = 0;
			wl->stored = 0;
			wl->words = nullptr;

			// Invoke and Verify Results
			assert(wl->missyElliot() == -1);
			break;
		}
		case 1: {
			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "Mal");
			num = 1;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->missyElliot() == 2);
			assert(strcmp("laM", wl->words[0]) == 0);

			break;
		}
		case 2: {
			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "be");
			num = 1;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->missyElliot() == 2);
			assert(strcmp("eb", wl->words[0]) == 0);

			break;
		}
		case 3: {

			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "a");
			num = 1;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->missyElliot() == 0);
			assert(strcmp("a", wl->words[0]) == 0);
			break;
		}
		case 4: {

			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "I");
			strcpy(testlist[1], "am");
			num = 2;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->missyElliot() == 2);
			assert(strcmp("ma", wl->words[0]) == 0);
			assert(strcmp("I", wl->words[1]) == 0);
			break;
		}
		case 5: {

			// Setup 
			int max = 5, // Keep track of the max number words	
				num = 0; // Number of words we can currently store
			//Allocate rows, to point to words
			char ** testlist = new char*[max];
			// for each row, allocate space for words
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize words
			strcpy(testlist[0], "I");
			strcpy(testlist[1], "am");
			strcpy(testlist[2], "teapot");
			num = 3;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->capacity = max;
			wl->stored = num;
			wl->words = testlist;

			// Invoke and Verify Results
			assert(wl->missyElliot() == 8);
			assert(strcmp("topaet", wl->words[0]) == 0);
			assert(strcmp("ma", wl->words[1]) == 0);
			assert(strcmp("I", wl->words[2]) == 0);
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}
}// namespace ZeroRelative
#endif
