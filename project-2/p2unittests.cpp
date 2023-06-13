#define MAKE_MEMBERS_PUBLIC
#include"wordlisttests_sp23.h"

//Test implemetations based on the "Front"
//defined as the zeroth element.
using namespace ZeroRelative;

int main() {

	runTest(test_ctor, 0);
	runTest(test_ctor, 1);
	runTest(test_ctor, 2);

	runTest(test_display, 0); 
	runTest(test_display, 1); 
	runTest(test_display, 2); 

	runTest(test_word, 0); 
	runTest(test_word, 1); 
	runTest(test_word, 2); 
	
	runTest(test_size, 0);
	runTest(test_size, 1);

	runTest(test_insert, 0); 
	runTest(test_insert, 1); 
	runTest(test_insert, 2); 
	runTest(test_insert, 3); 
	runTest(test_insert, 4); 
	runTest(test_insert, 5); 
	runTest(test_insert, 6); 
	runTest(test_insert, 7);
	runTest(test_insert, 8);
	runTest(test_insert, 9);
	runTest(test_insert, 10);
	runTest(test_insert, 11);
	runTest(test_insert, 12);
	runTest(test_insert, 13);


	runTest(test_remove, 0);
	runTest(test_remove, 1);
	runTest(test_remove, 2);
	runTest(test_remove, 3);
	runTest(test_remove, 4);

	runTest(test_prepend, 0);
	runTest(test_prepend, 1);
	runTest(test_prepend, 2);
	runTest(test_prepend, 3);
	runTest(test_prepend, 4);
	runTest(test_prepend, 5);
	runTest(test_prepend, 6);

	runTest(test_search, 0);
	runTest(test_search, 1);
	runTest(test_search, 2);
	runTest(test_search, 3);

	runTest(test_sort, 0);
	runTest(test_sort, 1);
	runTest(test_sort, 2);
	runTest(test_sort, 3);
	runTest(test_sort, 4);

	runTest(test_missy, 0);
	runTest(test_missy, 1);
	runTest(test_missy, 2);
	runTest(test_missy, 3);
	runTest(test_missy, 4);
	runTest(test_missy, 5);

	runTest(test_copyctor, 0);
	runTest(test_copyctor, 1);

	runTest(test_assignOper, 0);
	runTest(test_assignOper, 1);
	runTest(test_assignOper, 2);

//These two tests use the memory debugger
//Disable if debugmem.h not included.
#ifdef DEBUGMEM_H // if debugmem.h is included 
	//runTest(test_assignOper, 3); //DEBUGMEM_H

	//runTest(test_dtor, 0); //DEBUGMEM_H
#endif

	return 0;
}
