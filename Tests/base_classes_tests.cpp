//
// Created by Gabriel on 12/05/2021.
//

#include "test_utilities.h"
#include "../AVL Tree/avl_tree.h"
#include "../AVL Tree/exceptions.h"
#include "../Car Classes/car_sells.h"
#include "../Car Classes/car_best_sells.h"
#include "../Car Classes/car_zero_points.h"
#include "../Car Classes/car_points.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

#define NUMBER_TESTS 8

bool testCarPointsBasicFunctions(){
    bool result = true;
    CarPoints points = CarPoints(1,6, 15);
    CarPoints points2(points);
    CarPoints points3 = CarPoints(5,13, 200);

    ASSERT_TEST(points.getTypeId() == 1, returnLabel);
    ASSERT_TEST(points.getModel() == 6, returnLabel);
    ASSERT_TEST(points.getPoints() == 15, returnLabel);


    ASSERT_TEST(points2.getTypeId() == 1, returnLabel);
    ASSERT_TEST(points2.getModel() == 6, returnLabel);
    ASSERT_TEST(points2.getPoints() == 15, returnLabel);

    points2.updatePoints(100);
    ASSERT_TEST(points2.getPoints() == 115, returnLabel);


    points2 = points3;
    ASSERT_TEST(points2.getTypeId() == 5, returnLabel);
    ASSERT_TEST(points2.getModel() == 13, returnLabel);
    ASSERT_TEST(points2.getPoints() == 200, returnLabel);
    returnLabel:
    return result;
}


bool testCarPointsOperators(){
    bool result = true;
    CarPoints points1 = CarPoints(1,6, 15);
    CarPoints points2 = CarPoints(3, 4, -10);
    CarPoints points3 = CarPoints(2,8, 15);
    CarPoints points4 = CarPoints(1,8, 15);

    ASSERT_TEST(points1 == points1, returnLabel);

    ASSERT_TEST(points1 > points2, returnLabel);
    ASSERT_TEST(!(points2 > points1), returnLabel);
    ASSERT_TEST(points2 < points1, returnLabel);
    ASSERT_TEST(!(points1 < points2), returnLabel);

    ASSERT_TEST(points3 > points1, returnLabel);
    ASSERT_TEST(!(points1 > points3), returnLabel);
    ASSERT_TEST(points1 < points3, returnLabel);
    ASSERT_TEST(!(points3 < points1), returnLabel);

    ASSERT_TEST(points4 > points1, returnLabel);
    ASSERT_TEST(!(points1 > points4), returnLabel);
    ASSERT_TEST(points1 < points4, returnLabel);
    ASSERT_TEST(!(points4 < points1), returnLabel);
    returnLabel:
    return result;
}

bool testCarBestSellsBasicFunctions(){
    bool result = true;
    CarBestSells best = CarBestSells(1);
    best.updateBestSeller(8, 2);
    CarBestSells best2 = CarBestSells(4);
    CarBestSells best3(best);

    ASSERT_TEST(best.getTypeId() == 1, returnLabel);
    ASSERT_TEST(best.getBestSellerAmount() == 8, returnLabel);
    ASSERT_TEST(best.getBestSellerModel() == 2, returnLabel);

    ASSERT_TEST(best3.getTypeId() == 1, returnLabel);
    ASSERT_TEST(best3.getBestSellerAmount() == 8, returnLabel);
    ASSERT_TEST(best3.getBestSellerModel() == 2, returnLabel);

    ASSERT_TEST(best2.getTypeId() == 4, returnLabel);
    ASSERT_TEST(best2.getBestSellerAmount() == 0, returnLabel);
    ASSERT_TEST(best2.getBestSellerModel() == 0, returnLabel);

    best2 = best;

    ASSERT_TEST(best2.getTypeId() == 1, returnLabel);
    ASSERT_TEST(best2.getBestSellerAmount() == 8, returnLabel);
    ASSERT_TEST(best2.getBestSellerModel() == 2, returnLabel);

    returnLabel:
    return result;
}

bool testCarBestSellsOperators(){
    bool result = true;
    CarBestSells best = CarBestSells(1);
    best.updateBestSeller(8, 2);

    CarBestSells best2 = CarBestSells(2);
    best2.updateBestSeller(5, 3);

    CarBestSells best3 = CarBestSells(4);
    best3.updateBestSeller(8, 3);

    CarBestSells best4 = CarBestSells(1);
    best4.updateBestSeller(8, 3);

    ASSERT_TEST(best == best, returnLabel);

    ASSERT_TEST(best > best2, returnLabel);
    ASSERT_TEST(!(best2 > best), returnLabel);
    ASSERT_TEST(best2 < best, returnLabel);
    ASSERT_TEST(!(best < best2), returnLabel);

    ASSERT_TEST(best > best3, returnLabel);
    ASSERT_TEST(!(best3 > best), returnLabel);
    ASSERT_TEST(best3 < best, returnLabel);
    ASSERT_TEST(!(best < best3), returnLabel);

    ASSERT_TEST(best > best4, returnLabel);
    ASSERT_TEST(!(best4 > best), returnLabel);
    ASSERT_TEST(best4 < best, returnLabel);
    ASSERT_TEST(!(best < best4), returnLabel);
    returnLabel:
    return result;
}

bool testCarZeroPointsBasicFunctions(){
    bool result = true;
    bool passed = true;
    CarZeroPoints zero = CarZeroPoints(1, 10);
    CarZeroPoints zero2(zero);
    CarZeroPoints zero3 = CarZeroPoints(2, 5);

    AVLTree<int> models = zero.getModels();

    ASSERT_TEST(zero.getTypeId() == 1, returnLabel);
    ASSERT_TEST(!zero.emptyModels(), returnLabel);
    for(int i = 0; i < 10; i++){
        ASSERT_TEST(models.find(i), returnLabel);
    }

    try{
        passed = false;
        models.find(11);
    } catch(NodeDoesntExist& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    models.printTree();
    zero.removeModel(6);
    models = zero.getModels();

    try{
        passed = false;
        models.find(11);
    } catch(NodeDoesntExist& e){
        passed = true;
    }
    ASSERT_TEST(passed, returnLabel);

    zero.insertModel(6);
    models = zero.getModels();
    ASSERT_TEST(models.find(6), returnLabel);

    ASSERT_TEST(zero2.getTypeId() == 1, returnLabel);
    ASSERT_TEST(!zero2.emptyModels(), returnLabel);
    models = zero2.getModels();
    for(int i = 0; i < 10; i++){
        ASSERT_TEST(models.find(i), returnLabel);
    }

    zero3 = zero2;
    models = zero3.getModels();

    ASSERT_TEST(zero3.getTypeId() == 1, returnLabel);
    ASSERT_TEST(!zero3.emptyModels(), returnLabel);
    for(int i = 0; i < 10; i++){
        ASSERT_TEST(models.find(i), returnLabel);
    }

    returnLabel:
    return result;
}

bool testCarZeroPointsOperators(){
    bool result = true;
    CarZeroPoints zero = CarZeroPoints(1, 10);
    CarZeroPoints zero2 = CarZeroPoints(3, 10);

    ASSERT_TEST(zero == zero, returnLabel);

    ASSERT_TEST(zero2 > zero, returnLabel);
    ASSERT_TEST(!(zero > zero2), returnLabel);
    ASSERT_TEST(zero < zero2, returnLabel);
    ASSERT_TEST(!(zero2 < zero), returnLabel);
    returnLabel:
    return result;
}

bool testCarSellsBasicFunctions(){
    bool result = true;
    CarSells sells = CarSells(2, 12);
    CarSells sells2(sells);
    CarSells sells3 = CarSells(6, 4);

    sells3 = sells;

    ASSERT_TEST(sells.getTypeId() == 2 ,returnLabel);
    ASSERT_TEST(sells.getNumOfModels() == 12 ,returnLabel);
    ASSERT_TEST(sells2.getTypeId() == 2 ,returnLabel);
    ASSERT_TEST(sells2.getNumOfModels() == 12 ,returnLabel);
    ASSERT_TEST(sells3.getTypeId() == 2 ,returnLabel);
    ASSERT_TEST(sells3.getNumOfModels() == 12 ,returnLabel);

    returnLabel:
    return result;
}

bool testCarSellsOperators(){
    bool result = true;

    CarSells sells = CarSells(2, 12);
    CarSells sells2 = CarSells(6, 4);

    ASSERT_TEST(sells == sells, returnLabel);

    ASSERT_TEST(sells2 > sells, returnLabel);
    ASSERT_TEST(!(sells > sells2), returnLabel);
    ASSERT_TEST(sells < sells2, returnLabel);
    ASSERT_TEST(!(sells2 < sells), returnLabel);

    returnLabel:
    return result;
}

/* bool test(){
    bool result = true;

returnLabel:
    return result;
} */


bool (*tests[]) (void) = {
        testCarPointsBasicFunctions,
        testCarPointsOperators,
        testCarBestSellsBasicFunctions,
        testCarBestSellsOperators,
        testCarZeroPointsBasicFunctions,
        testCarZeroPointsOperators,
        testCarSellsBasicFunctions,
        testCarSellsOperators,
};

const char* testNames[] = {
        "testCarPointsBasicFunctions",
        "testCarPointsOperators",
        "testCarBestSellsBasicFunctions",
        "testCarBestSellsOperators",
        "testCarZeroPointsBasicFunctions",
        "testCarZeroPointsOperators",
        "testCarSellsBasicFunctions",
        "testCarSellsOperators",
        "testCarSellsSellFunctions"
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