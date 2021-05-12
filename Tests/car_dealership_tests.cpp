//
// Created by Gabriel on 12/05/2021.
//

#include "test_utilities.h"
#include "../Car manager/library.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

#define NUMBER_TESTS 1

bool testDSInit(){
    bool result = true;
    void* ds = Init();
    void* ds_ptr;
    ASSERT_TEST(AddCarType(ds, 1, 10) == SUCCESS ,returnLabel);
    ASSERT_TEST(RemoveCarType(ds, 1) == SUCCESS ,returnLabel);
    ds_ptr = &ds;
    Quit(&ds_ptr);
    ASSERT_TEST(ds == NULL ,returnLabel);
    returnLabel:
    return result;
}


/* bool test(){
    bool result = true;

returnLabel:
    return result;
} */

bool (*tests[]) (void) = {
        testDSInit,

};

const char* testNames[] = {
        "testDSInit",

};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        for (int test_idx = 0; test_idx < NUMBER_TESTS; test_idx++) {
            RUN_TEST(tests[test_idx], testNames[test_idx]);
        }
        return 0;
    }
    if (argc != 2) {
        fprintf(stdout, "Usage: priority_queue_tests <test index>\n");
        return 0;
    }

    int test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > NUMBER_TESTS) {
        fprintf(stderr, "Invalid test index %d\n", test_idx);
        return 0;
    }

    RUN_TEST(tests[test_idx - 1], testNames[test_idx - 1]);
    return 0;
}