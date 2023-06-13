#ifndef PROJECT3_DLLTEST_H
#define PROJECT3_DLLTEST_H

#define MAKE_MEMBERS_PUBLIC

#include<iostream>
#include <fstream>
#include <sstream> 
#include<string>
#include<iterator>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<functional>

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
#include"dllist.h"



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


//Test empty
int test_empty(int testNum) {
	std::cout <<__func__ <<testNum << std::endl;
	std::string name = std::string(__func__);
	switch (testNum) {
	case 0: {
		
		DLList<int> * l = new DLList<int>;

		assert(l->empty() == true);

		break;
	}
	case 1: {
		
		//Make some control nodes
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->empty() == false);
		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;
}


//Test insert_front
int test_insert_front(int testNum) {
	std::cout << __func__ << testNum << std::endl;
	std::string name = std::string(__func__);

	switch (testNum) {
	case 0: {

		DLList<int> * l = new DLList<int>;

		l->insert_front(99);

		assert(l->front != nullptr);
		assert(l->rear != nullptr);

		assert(l->front->prev() == nullptr);
		assert(l->front->next() == nullptr);
		
		assert(l->front->value() == 99);
		assert(l->size == 1);

		break;
	}
	case 1: {
	
		//Make some control nodes
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		//Now with the list given a complete and correct starting state
		//We can test various member functions for correctness.
		//For example we can use this as one test for insert_front;
		l->insert_front("Zero");

		//Examing the final state of our list after call
		assert(l->size == 4); // pass
		assert(l->front != nullptr); //pass
		assert(l->front->prev() == nullptr);
		assert(l->front == front->prev());
		assert(l->front->next() == front);
		assert(l->front->value() == "Zero");
		assert(l->rear == third);
		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;
}

//Test insert_rear
int test_insert_rear(int testNum) {
	std::cout << __func__ << testNum << std::endl;
	std::string name = std::string(__func__);
	switch (testNum) {
	case 0: {

		DLList<int> * l = new DLList<int>;

		l->insert_rear(99);
		assert(l->front != nullptr);
		assert(l->rear != nullptr);
		assert(l->front->prev() == nullptr);
		assert(l->front->next() == nullptr);
		assert(l->front->value() == 99);
		assert(l->size == 1);
		break;
	}
	case 1: {

			 //Make some control nodes
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		//Now with the list given a complete and correct starting state
		//We can test various member functions for correctness.
		//For example we can use this as one test for insert_rear;
		l->insert_rear("forth");

		//Examing the final state of our list after call
		assert(l->size == 4);
		assert(l->front != nullptr);
		assert(l->rear != nullptr);
		assert(l->front == front);
		assert(l->rear->next() == nullptr);
		assert(l->rear->value() == "forth");
		assert(l->rear->prev() == third);
		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;
}

//Test insert
int test_insert(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl;
	switch (testNum) {
	case 0: {
		
		DLList<int> * l = new DLList<int>;

		l->insert(0, 1);

		assert(l->front != nullptr);
		assert(l->rear != nullptr);

		assert(l->size == 1);
		assert(l->front->value() == 1);
		assert(l->front == l->rear);
		
		assert(l->front->next() == nullptr);
		assert(l->front->prev() == nullptr);
		break;
		
	}
	case 1: {
	
		DLList<int> * l = new DLList<int>;

		l->insert(-1, 1);

		assert(l->front != nullptr);
		assert(l->rear != nullptr);

		assert(l->size == 1);
		assert(l->front->value() == 1);
		assert(l->front == l->rear);
		
		assert(l->front->next() == nullptr);
		assert(l->front->prev() == nullptr);
		break;
	}
	case 2: {
		DLList<int> * l = new DLList<int>;

		l->insert(99, 1);

		assert(l->front != nullptr);
		assert(l->rear != nullptr);
		assert(l->front->value() == 1);
		assert(l->size == 1);
		assert(l->front == l->rear);
		assert(l->front->next() == nullptr);
		assert(l->front->prev() == nullptr);
		break;
	}
	case 3: {
		//Make some control nodes
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = second;
		l->size = 2;

		l->insert(0, "Zero");

		//Examing the final state of our list after call
		assert(l->front != nullptr);
		assert(l->rear != nullptr);
		assert(l->size == 3);
		assert(l->front->prev() == nullptr);
		assert(l->front == front->prev());
		assert(l->front->next() == front);
		assert(l->front->value() == "Zero");
		assert(l->rear == second);

		break;
	}
	case 4: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = second;
		l->size = 2;

		l->insert(-1, "Zero");

		//Examing the final state of our list after call
		assert(l->front != nullptr);
		assert(l->rear != nullptr);
		assert(l->size == 3);
		assert(l->front->prev() == nullptr);
		assert(l->front == front->prev());
		assert(l->front->next() == front);
		assert(l->front->value() == "Zero");
		assert(l->rear == second);

		break;
	}
	case 5: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = second;
		l->size = 2;

		l->insert(4, "third");
	
		//Examing the final state of our list after call
		assert(l->front != nullptr);
		assert(l->rear != nullptr);
		assert(l->size == 3);
		assert(l->front == front);
		assert(l->rear->next() == nullptr);
		assert(l->rear->value() == "third");
		assert(l->rear->prev() == second);
		break;
	}
	case 6: { 
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = second;
		l->size = 2;

		l->insert(1, "half");
	
		//Examing the final state of our list after call
		assert(l->size == 3);
		assert(l->front == front);

		assert(l->front != nullptr);
		assert(l->rear != nullptr);

		assert(l->front->prev() == nullptr); 
		assert(l->front->next()->value() == "half"); 
		assert(l->rear->prev() == l->front->next()); 
		assert(l->rear == second); 
		assert(l->rear->next() == nullptr); 
		assert(l->front->next()->next() == l->rear); 
		assert(l->front == l->rear->prev()->prev()); 
		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;
}

//Test find
int test_find(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl;
	switch (testNum) {
	case 0: {
		DLList<int> * l = new DLList<int>;

		assert(l->find(100)==-1);

		break;
	}
	case 1: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		//Examing the final state of our list after call
		assert(l->find("Zero") == -1);
	
		break;
	}
	case 2: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		//Examing the final state of our list after call

		assert(l->find("first") == 0);

		break;
	}
	case 3: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		//Examing the final state of our list after call

		assert(l->find("second") == 1);

		break;
	}
	case 4: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		//Examing the final state of our list after call
		assert(l->find("third") == 2);
		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;
		

	}
	return 0;
}

//Test peek_front
int test_peek_front(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl;
	switch (testNum) {
	case 0: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);


		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->peek_front() == "first");
		break;
	}
	case 1: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->peek_front() == "first");
		break;
	}

	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;
	

	}
	return 0;
}


//Test peek_rear
int test_peek_rear(int testNum) {
	std::string name = std::string(__func__);
	
	std::cout << __func__ << testNum << std::endl;
	switch (testNum) {
	case 0: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->peek_rear() == "first");
		break;
	}
	case 1: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->peek_rear() == "third");
		break;
	}

	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;
}
//Test peek
int test_peek(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl;
	switch (testNum) {
	case 0: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);


		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->peek(0) == "first");
		break;
	}
	case 1: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->peek(0) == "first");
		assert(l->peek(1) == "second");
		assert(l->peek(2) == "third");
		break;
	}
	
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;
	}
	return 0;
}

//Test remove_front
int test_remove_front(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl;
	switch (testNum) {
	case 0: {
		DLList<int> * l = new DLList<int>;
		assert(l->remove_front() == false);
		break;
	}
	case 1: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);


		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->remove_front() == true);
		assert(l->size == 0);
		assert(l->front == nullptr);
		assert(l->rear == nullptr);
		break;
	}
	case 2: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->remove_front() == true);
		assert(l->size == 2);
		assert(l->front == second);
		assert(l->rear == third);
		assert(l->front->prev() == nullptr);
		break;
	}
	
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;
}
//Test remove_rear
int test_remove_rear(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl;
	switch (testNum) {
	case 0: {
		DLList<int> * l = new DLList<int>;
		assert(l->remove_rear() == false);
		break;

	}
	case 1: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);


		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->remove_rear() == true);
		assert(l->size == 0);
		assert(l->front == nullptr);
		assert(l->rear == nullptr);
		break;
	}
	case 2: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->remove_rear() == true);
		assert(l->size == 2);
		assert(l->front == front);
		assert(l->rear == second);
		assert(l->rear->next() == nullptr);
		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;
	}
	return 0;
}


int test_remove_index(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl <<std::flush;
	switch (testNum) {
	case 0: {
		DLList<int> * l = new DLList<int>;
		assert(l->remove_index(-1) == false);
		break;
	}
	case 1: {
		DLList<int> * l = new DLList<int>;
		assert(l->remove_index(9999) == false);
		break;
	}
	case 2: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->remove_index(-1) == false);

		break;
	}
	case 3: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);


		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->remove_index(9999) == false);

		break;
	}
	case 4: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);


		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->remove_index(0) == true);
		assert(l->size == 0);
		assert(l->front == nullptr);
		assert(l->rear == nullptr);
		break;
	}
	case 5: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->remove_index(0) == true);
		assert(l->size == 2);
		assert(l->front == second);
		assert(l->front->prev() == nullptr);
		assert(l->rear == third);
		break;

	}
	case 6: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->remove_index(2) == true);
		assert(l->size == 2);
		assert(l->front == front);
		assert(l->rear->next() == nullptr);
		assert(l->rear == second);
		break;

	}
	case 7: { 
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;
        

		assert(l->remove_index(1) == true);
		assert(l->size == 2);

		assert(l->front == front);
		assert(l->rear == third);

		assert(l->front->next() == third);
		assert(l->rear->prev() == front);
		break;


	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;
}

int test_remove_value(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl << std::flush;
	switch (testNum) {
	case 0: {//Test with empty list
		DLList<int> * l = new DLList<int>;
		assert(l->remove_value(1) == -1);
		break;
	}
	case 1: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->remove_value("second") == -1);

		break;
	}

	case 2: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(nullptr);


		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->remove_value("first") == 0);
		assert(l->size == 0);
		assert(l->front == nullptr);
		assert(l->rear == nullptr);
		break;
	}
	case 3: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->remove_value("first") == 0);
		assert(l->size == 2);
		assert(l->front == second);
		assert(l->front != nullptr);
		assert(l->front->prev() == nullptr);
		assert(l->rear == third);
		break;

	}
	case 4: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->remove_value("third") == 2);
		assert(l->size == 2);
		assert(l->front == front);
		assert(l->rear != nullptr);
		assert(l->rear->next() == nullptr);
		assert(l->rear == second);
		break;

	}
	case 5: {
		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value("first");
		front->prev(nullptr);
		front->next(second);

		second->value("second");
		second->prev(front);
		second->next(third);

		third->value("third");
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->remove_value("second") == 1);
		assert(l->size == 2);

		assert(l->front == front);
		assert(l->rear == third);

		assert(l->front != nullptr);
		assert(l->rear != nullptr);
		assert(l->front->next() == third);
		assert(l->rear->prev() == front);

		break;


	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;
}
int test_print(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl << std::flush;
	switch (testNum) {
	case 0: {

		std::string test_string1("Tom Dick Mary"); 
		std::stringstream buffer(test_string1);
		std::vector<std::string> test_vector{ std::istream_iterator<std::string>(buffer), std::istream_iterator<std::string>() };
		buffer.str("");

		DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
		DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

		//Link together to make a valid linked list 
		front->value(test_vector[0]);
		front->prev(nullptr);
		front->next(second);

		second->value(test_vector[1]);
		second->prev(front);
		second->next(third);

		third->value(test_vector[2]);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

		l->print();
		std::cout.rdbuf(old);


		std::string text = buffer.str();

		std::vector<std::string> ret{ std::istream_iterator<std::string>(buffer),
			std::istream_iterator<std::string>() };

		assert(text.length() == test_string1.length());
		assert(text == test_string1);
		for (int i = 0; i < ret.size(); i++) {
			assert(ret[i] == test_vector[i]);
		}



		break;

	}
	case 1: {

		std::string test_string1("");
		std::stringstream buffer(test_string1);
		std::vector<std::string> test_vector{ std::istream_iterator<std::string>(buffer), std::istream_iterator<std::string>() };
		buffer.str("");

		//Assume Constructor Correctly Implemented
		DLList<std::string> * l = new DLList<std::string>;

		//hijack cout buffer
		std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

		l->print();

		//restore cout buffer
		std::cout.rdbuf(old);

		std::string text = buffer.str();
		std::vector<std::string> ret{ std::istream_iterator<std::string>(buffer),
			std::istream_iterator<std::string>() };

		assert(text.length() == test_string1.length() );
		assert(text == test_string1);
		for (int i = 0; i < ret.size(); i++) {
			assert(ret[i] == test_vector[i]);
		}

		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;

}
int test_count(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl << std::flush;
	switch (testNum) {
	case 0: {

		DLList<int>::DLNode* front = new DLList<int>::DLNode;
		DLList<int>::DLNode* second = new DLList<int>::DLNode;
		DLList<int>::DLNode* third = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->count() == 3);

		break;

	}
	case 1: {
		DLList<std::string> * l = new DLList<std::string>;
		assert(l->count() == 0);
		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;

}
int test_count_value(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl << std::flush;
	switch (testNum) {
	case 0: {

		DLList<int>::DLNode* front = new DLList<int>::DLNode;
		DLList<int>::DLNode* second = new DLList<int>::DLNode;
		DLList<int>::DLNode* third = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->count_value(42) == 0);

		break;

	}
	case 1: {
		DLList<int> * l = new DLList<int>;
		assert(l->count_value(10) == 0);
		break;
	}
	case 2: {

		DLList<int>::DLNode* front = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->count_value(8) == 0);
		break;
	}
	case 3: {

		DLList<int>::DLNode* front = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = front;
		l->size = 1;

		assert(l->count_value(2) == 1);
		break;
	}
	case 4: {
		
		DLList<int>::DLNode* front = new DLList<int>::DLNode;
		DLList<int>::DLNode* second = new DLList<int>::DLNode;
		DLList<int>::DLNode* third = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->count_value(2) == 1);
		break;
	}
	case 5: {
		
		DLList<int>::DLNode* front = new DLList<int>::DLNode;
		DLList<int>::DLNode* second = new DLList<int>::DLNode;
		DLList<int>::DLNode* third = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(2);
		second->prev(front);
		second->next(third);

		third->value(2);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		assert(l->count_value(2) == 3);
		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;

}

int test_copyCtor(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl << std::flush;
	switch (testNum) {
	case 0: {

		DLList<int> * l = new DLList<int>;
		DLList<int> * p = new DLList<int>(*l);

		//Set up the initial state of the list to test
		assert(p->front==nullptr);
		assert(p->rear == nullptr);
		assert(p->size == 0);

		break;

	}

	case 1: {


		DLList<int>::DLNode* front = new DLList<int>::DLNode;
		DLList<int>::DLNode* second = new DLList<int>::DLNode;
		DLList<int>::DLNode* third = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;
		 
		DLList<int> * p = new DLList<int>(*l);

		assert(p->front != nullptr );
		assert(p->rear != nullptr);
		assert(p->size == 3);

		assert(p->front->value() == front->value());
		assert(p->front->next()->value() == second->value());
		assert(p->rear->prev()->value() == second->value());
		assert(p->rear->value() == third->value());

		assert(p->front != front);
		assert(p->rear != third);

		break;


	}
	case 2: {
		DLList<int>::DLNode* front = new DLList<int>::DLNode;
		DLList<int>::DLNode* second = new DLList<int>::DLNode;
		DLList<int>::DLNode* third = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		DLList<int> * p = new DLList<int>(*l);

		assert(p->front != nullptr);
		assert(p->rear != nullptr);
		assert(p->size == 3);

		assert(p->front->value() == front->value());
		assert(p->front->next()->value() == second->value());
		assert(p->rear->prev()->value() == second->value());
		assert(p->rear->value() == third->value());


		//check aliasing
		assert(p->front != front);
		assert(p->front != second);
		assert(p->front != third);

		assert(p->front->next() != front);
		assert(p->front->next() != second);
		assert(p->front->next() != third);

		assert(p->rear != front);
		assert(p->rear != second);
		assert(p->rear != third);

		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;

}


int test_assgnOper(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl << std::flush;
	switch (testNum) {
	case 0: {

		DLList<int> * l = new DLList<int>;
		DLList<int> * p = new DLList<int>;

		*p = *l;
		//Set up the initial state of the list to test

		assert(p->front == nullptr);
		assert(p->rear == nullptr);
		assert(p->size == 0);

		break;

	}

	case 1: {

		DLList<int>::DLNode* front = new DLList<int>::DLNode;
		DLList<int>::DLNode* second = new DLList<int>::DLNode;
		DLList<int>::DLNode* third = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		DLList<int> * p = new DLList<int>;

		*p = *l;

		assert(p->front != nullptr);
		assert(p->rear != nullptr);
		assert(p->size == 3);


		assert(p->front->value() == front->value());
		assert(p->front->next()->value() == second->value());
		assert(p->rear->prev()->value() == second->value());
		assert(p->rear->value() == third->value());

		assert(p->front != front);
		assert(p->rear != third);

		break;


	}
	
	case 2: {
		DLList<int>::DLNode* front = new DLList<int>::DLNode;
		DLList<int>::DLNode* second = new DLList<int>::DLNode;
		DLList<int>::DLNode* third = new DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;

		DLList<int> * p = new DLList<int>;

		*p = *l;

		assert(p->front != nullptr);
		assert(p->rear != nullptr);
		assert(p->front->next() != nullptr);
		assert(p->rear->prev() != nullptr);

		assert(p->size == 3);

		assert(p->front->value() == front->value());
		assert(p->front->next()->value() == second->value());
		assert(p->rear->prev()->value() == second->value());
		assert(p->rear->value() == third->value());


		//check aliasing
		assert(p->front != front);
		assert(p->front != second);
		assert(p->front != third);

		assert(p->front->next() != front);
		assert(p->front->next() != second);
		assert(p->front->next() != third);

		assert(p->rear != front);
		assert(p->rear != second);
		assert(p->rear != third);

		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;

	}
	return 0;

}


int test_mem_destructor(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl << std::flush;
	switch (testNum) {
	case 0: {
		RESET();
		DLList<int>::DLNode* front = DEBUG_NEW DLList<int>::DLNode;
		DLList<int>::DLNode* second = DEBUG_NEW DLList<int>::DLNode;
		DLList<int>::DLNode* third = DEBUG_NEW DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);

		//Assume Constructor Correctly Implemented
		{
			DLList<int> * l = new DLList<int>;

			//Set up the initial state of the list to test
			l->front = front;
			l->rear = third;
			l->size = 3;

			//destructor
			delete l;
		} 

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

int test_mem_assgnOper(int testNum) {
	std::string name = std::string(__func__);
	std::cout << __func__ << testNum << std::endl << std::flush;
	switch (testNum) {
	case 0: {
		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;
		DLList<int> * p = new DLList<int>;

		RESET(); 

		DLList<int>::DLNode* front = DEBUG_NEW DLList<int>::DLNode;
		DLList<int>::DLNode* second = DEBUG_NEW DLList<int>::DLNode;
		DLList<int>::DLNode* third = DEBUG_NEW DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);


		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;
				
		*l = *p;

		//GETMEMORYREPORT();
		if (SIZE() != 0) {
			std::cerr << "Assign Op: Memory Leak detected" << std::endl;
		}
		assert(SIZE() == 0);
		break;
	}
	case 1: {

		//Assume Constructor Correctly Implemented
		DLList<int> * l = new DLList<int>;

		RESET();
		DLList<int>::DLNode* front = DEBUG_NEW DLList<int>::DLNode;
		DLList<int>::DLNode* second = DEBUG_NEW DLList<int>::DLNode;
		DLList<int>::DLNode* third = DEBUG_NEW DLList<int>::DLNode;

		//Link together to make a valid linked list 
		front->value(2);
		front->prev(nullptr);
		front->next(second);

		second->value(4);
		second->prev(front);
		second->next(third);

		third->value(76);
		third->prev(second);
		third->next(nullptr);

	
		//Set up the initial state of the list to test
		l->front = front;
		l->rear = third;
		l->size = 3;
		//GETMEMORYREPORT();

		*l = *l;
		if (SIZE() != 3) {
			std::cerr << "Assign Op: Improper assignment" << std::endl;
		}
		assert(SIZE() == 3);
		break;
	}
	default:
		std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
		return -1;
	}
	return 0;

}


#endif
