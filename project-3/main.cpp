
// Choose which run to compile
#define RUN0 //RUN1 RUN2 RUN3


#ifdef RUN0 

#include"dllist.h"
#include"studentinfo.h"
#include<iostream>

int main() {
	std::cout << StudentInfo::name() << std::endl;
	std::cout << StudentInfo::id() << std::endl;

	DLList<int> * l = new DLList<int>;; //DLList of integers

	l->insert_front(5);
    l->insert_rear(4);
    l->print();
	std::cout << l->peek_front() << std::endl;

	return 0;

}

 #elif defined RUN1

#include"dllist.h"
#include"studentinfo.h"
#include<iostream>
#include<string>

int main() {

	std::cout << StudentInfo::name() << std::endl;
	std::cout << StudentInfo::id() << std::endl;

	DLList<std::string> * l = new DLList<std::string>; //DLList of integers

	l->insert_rear("Hello");
	l->insert_front("World");
	l->insert_front("Bob");
	l->insert_front("2");

	l->print(); // 2 Bob World Hello
	l->remove_rear();  // Will trip assert if empty
	l->print(); // 2 Bob World 

	std::cout << l->peek_front() << std::endl; // 2

	return 0;

}

 #elif defined RUN2

#define MAKE_MEMBERS_PUBLIC
#include"dllist.h"
#include<assert.h>

//Unit test example for push_font on initially empty list

int main() {

	// Step 1: Initial state
	// Assume that constructor implemented properly
	// If you're not sure if the constructor is 
	// implemented properly, STOP, go back and make
	// sure. Luckily the default constructor is 
	// done for you.  But the point remains, never,
	// ever, use a function in a test that isn't itself
	// verified to function according to spec.
	DLList<int> * l = new DLList<int>;


	// Step 2: Execute the function to test
	l->insert_front(99);

	// Step 3: Verify what you expect to observe.
	// You must know what is supposed to happen in
	// order to analyze for correctness. Generally, 
	// you must permute all possible combinations
	// of all member variables.
	assert(l->front != nullptr);
	assert(l->rear != nullptr);
	assert(l->size == 1);
	assert(l->front->prev() == nullptr);
	assert(l->front->next() == nullptr);
	assert(l->front->value() == 99);

	return 0;
}

#elif defined RUN3

#define MAKE_MEMBERS_PUBLIC
#include"dllist.h"
#include<assert.h>
#include<string>

//Unit test example for push_font on initially non empty list

int main() {

	// Step 1: Initial state
	// Same as above, except we must front populate the list
	// However, since we are testing insert_front, we cannot
	// use it to generate the initial state of our list
	// to test.  So we have to manually set the initial state
	// in this case we are creating a list with three nodes.
	DLList<std::string>::DLNode* front = new DLList<std::string>::DLNode;
	DLList<std::string>::DLNode* second = new DLList<std::string>::DLNode;
	DLList<std::string>::DLNode* third = new DLList<std::string>::DLNode;

	// We have to manually linked everything together:
	front->value("first");
	front->prev(nullptr);
	front->next(second);

	second->value("second");
	second->prev(front);
	second->next(third);

	third->value("third");
	third->prev(second);
	third->next(nullptr);

	// Now we create  DLList object and inject the initial control state:
	DLList<std::string> * l = new DLList<std::string>;
	l->front = front;
	l->rear = third;
	l->size = 3;

	// Step 2: Now with the list given a complete and correct starting state
	// We can test various member functions for correctness.
	// For example we can use this as one test for insert_front;
	l->insert_front("Zero");

	// Step 3: Verify:  Technically, we should examine all 
	// member variables, and all nodes' value, nxt, prv pointers
	// to ensure that the insert_front didn't mangle any of the
	// internal nodes.  But, this is mostly just to illustrate
	// how you might develop your own tests.  
	assert(l->size == 4);
	assert(l->front->prev() == nullptr);
	assert(l->front == front->prev());
	assert(l->front->next() == front);
	assert(l->front->value() == "Zero");
	assert(l->rear == third);

	return 0;
}

#else 


#include"listtests_s23.h"
int main() {
	runTest(test_empty, 0);

	return 0;
}

 #endif
