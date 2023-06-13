

#define MAKE_MEMBERS_PUBLIC
#include "listtests_s23.h"

int main() {

//Test empty 0,1 

    runTest(test_empty, 0); // Passed
    runTest(test_empty, 1); // Passed

//Test insert_front 0,1

    runTest(test_insert_front, 0);  // Passed
    runTest(test_insert_front, 1); // Passed

//Test insert_rear 0,1

    runTest(test_insert_rear, 0); // Passed
    runTest(test_insert_rear, 1); // Passed

//Test insert 0,1,2,3,4,5,6

    runTest(test_insert, 0); // Passed
    runTest(test_insert, 1); // Passed
    runTest(test_insert, 2);// Passed
    runTest(test_insert, 3);// Passed
    runTest(test_insert, 4);// Passed
    runTest(test_insert, 5);
    runTest(test_insert, 6);

//Test find 0,1,2,3,4

    runTest(test_find, 0);
    runTest(test_find, 1);
    runTest(test_find, 2);
    runTest(test_find, 3);
    runTest(test_find, 4);

//Test peek_front 0,1

    runTest(test_peek_front, 0);
    runTest(test_peek_front, 1);

//Test peek_rear 0,1

    runTest(test_peek_rear, 0);
    runTest(test_peek_rear, 1);

//Test peek 0,1

    runTest(test_peek, 0);
    runTest(test_peek, 1);

//Test remove_front 0,1,2

    runTest(test_remove_front, 0);
    runTest(test_remove_front, 1);
    runTest(test_remove_front, 2);

//Test remove_rear 0, 1, 2

    runTest(test_remove_rear, 0);
    runTest(test_remove_rear, 1);
    runTest(test_remove_rear, 2);

// Test remove_index 0,1,2,3,4,5,6,7

    runTest(test_remove_index, 0);
    runTest(test_remove_index, 1);
    runTest(test_remove_index, 2);
    runTest(test_remove_index, 3);
    runTest(test_remove_index, 4);
    runTest(test_remove_index, 5);
    runTest(test_remove_index, 6);
    runTest(test_remove_index, 7);

// test remove_value 0,1,2,3,4,5

    runTest(test_remove_value, 0);
    runTest(test_remove_value, 1);
    runTest(test_remove_value, 2);
    runTest(test_remove_value, 3);
    runTest(test_remove_value, 4);
    runTest(test_remove_value, 5);

// Test print 0,1 

    runTest(test_print, 0);
    runTest(test_print, 1);

// Test count 0,1

    runTest(test_count, 0);
    runTest(test_count, 1);

// Test count_value 0,1,2,3,4,5

    runTest(test_count_value, 0);
    runTest(test_count_value, 1);
    runTest(test_count_value, 2);
    runTest(test_count_value, 3);
    runTest(test_count_value, 4);
    runTest(test_count_value, 5);

// Test copyCtor 0,1,2

    runTest(test_copyCtor, 0);
    runTest(test_copyCtor, 1);
    runTest(test_copyCtor, 2);

// Test assgnOper 0,1,2

    runTest(test_assgnOper, 0);
    runTest(test_assgnOper, 1);
    runTest(test_assgnOper, 2);

// Test mem_destructor 0


    runTest(test_mem_destructor, 0);

// Test mem_assgnOper 0,1

    runTest(test_mem_assgnOper, 0);
    runTest(test_mem_assgnOper, 1);

	return 0;
}
