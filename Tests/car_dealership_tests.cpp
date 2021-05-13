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

#define NUMBER_TESTS 3

void print_worst_models(int* type, int* model, int n){
    for(int i = 0; i < n; i++){
        cout << "Worst #" << i+1 << ": (type " << type[i] << ",model " << model[i] << ")" <<endl;
    }
}

bool testDSInit(){
    bool result = true;
    void* ds = Init();
    void** ds_ptr;
    ASSERT_TEST(AddCarType(ds, 1, 10) == SUCCESS ,returnLabel);
    ASSERT_TEST(RemoveCarType(ds, 1) == SUCCESS ,returnLabel);
    ds_ptr = &ds;
    Quit(ds_ptr);
    ASSERT_TEST(ds == NULL ,returnLabel);
    returnLabel:
    return result;
}

bool testDSBasic1(){
    bool result = true;
    void* ds = Init();
    void** ds_ptr = &ds;
    int best_model_id = -1;
    int worst_num = 5;
    int worst_model_types[worst_num];
    int worst_model_ids[worst_num];

    ASSERT_TEST(AddCarType(ds, 1, 5) == SUCCESS ,returnLabel);
    for(int i = 0; i < 4; i++){
        ASSERT_TEST(sellCar(ds, 1, 1) == SUCCESS ,returnLabel);
    }
    ASSERT_TEST(sellCar(ds, 1, 4) == SUCCESS ,returnLabel);
    ASSERT_TEST(sellCar(ds, 1, 3) == SUCCESS ,returnLabel);
    ASSERT_TEST(sellCar(ds, 1, 3) == SUCCESS ,returnLabel);
    ASSERT_TEST(sellCar(ds, 1, 2) == SUCCESS ,returnLabel);
    ASSERT_TEST(sellCar(ds, 1, 0) == SUCCESS ,returnLabel);
    ASSERT_TEST(makeComplaint(ds, 1, 0, 10) == SUCCESS ,returnLabel);
    ASSERT_TEST(makeComplaint(ds, 1, 2, 5) == SUCCESS ,returnLabel);
    ASSERT_TEST( GetWorstModels(ds, worst_num, worst_model_types, worst_model_ids)== SUCCESS ,returnLabel);
    print_worst_models(worst_model_types, worst_model_ids, worst_num);

    returnLabel:
    Quit(ds_ptr);
    return result;
}

bool testDSRating1(){
    bool result = true;
    void* ds = Init();
    void** ds_ptr = &ds;
    int best_model_id = -1;
    int worst_num = 15;
    int worst_model_types[worst_num];
    int worst_model_ids[worst_num];
    /*
     * Rating Table:
     * Type 1:
     * 1 : 83 points
     * 6 : -70 points
     * 8 : -880 points
     * 9 : 83 points
     * for(int i = 0; i < ; i++){

        }
     * */
    ASSERT_TEST(AddCarType(ds, 1, 10) == SUCCESS ,returnLabel);
    ASSERT_TEST(AddCarType(ds, 2, 8) == SUCCESS ,returnLabel);
    ASSERT_TEST(AddCarType(ds, 3, 17) == SUCCESS ,returnLabel);
    ASSERT_TEST(AddCarType(ds, 4, 22) == SUCCESS ,returnLabel);

    for(int i = 0; i < 10; i++){
        ASSERT_TEST(sellCar(ds, 1, 1) == SUCCESS ,returnLabel);
        ASSERT_TEST(sellCar(ds, 1, 9) == SUCCESS ,returnLabel);
    }
    ASSERT_TEST(makeComplaint(ds, 1, 1, 10) == SUCCESS ,returnLabel);
    ASSERT_TEST(makeComplaint(ds, 1, 1, 20) == SUCCESS ,returnLabel);
    ASSERT_TEST(makeComplaint(ds, 1, 1, 50) == SUCCESS ,returnLabel);
    for(int i = 0; i < 3; i++){
        ASSERT_TEST(sellCar(ds, 1, 6) == SUCCESS ,returnLabel);
    }

    for(int i = 0; i < 12; i++){
        ASSERT_TEST(sellCar(ds, 1, 8) == SUCCESS ,returnLabel);
    }

    ASSERT_TEST(makeComplaint(ds, 1, 9, 10) == SUCCESS ,returnLabel);


    ASSERT_TEST(makeComplaint(ds, 1, 9, 20) == SUCCESS ,returnLabel);

    ASSERT_TEST(RemoveCarType(ds, 4) == SUCCESS ,returnLabel);


    ASSERT_TEST(makeComplaint(ds, 1, 9, 50) == SUCCESS ,returnLabel);

    ASSERT_TEST(makeComplaint(ds, 1, 6, 1) == SUCCESS ,returnLabel);

    for(int i = 0; i < 10; i++){
        ASSERT_TEST(makeComplaint(ds, 1, 8, 1) == SUCCESS ,returnLabel);
    }

    ASSERT_TEST(GetBestSellerModelByType(ds, 3, &best_model_id) == SUCCESS ,returnLabel);
    ASSERT_TEST(best_model_id == 0 ,returnLabel);

    ASSERT_TEST(GetBestSellerModelByType(ds, 0, &best_model_id) == SUCCESS ,returnLabel);
    ASSERT_TEST(best_model_id == 8 ,returnLabel);

    ASSERT_TEST( GetWorstModels(ds, worst_num, worst_model_types, worst_model_ids)== SUCCESS ,returnLabel);
    print_worst_models(worst_model_types, worst_model_ids, worst_num);


    returnLabel:
    Quit(ds_ptr);
    return result;
}

/* bool test(){
    bool result = true;

returnLabel:
    return result;
} */

bool (*tests[]) (void) = {
        testDSInit,
        testDSBasic1,
        testDSRating1

};

const char* testNames[] = {
        "testDSInit",
        "testDSBasic1",
        "testDSRating1"
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