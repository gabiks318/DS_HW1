//
// Created by Gabriel on 08/05/2021.
//

#ifndef DS_HW1_CAR_DEALERSHIP_H
#define DS_HW1_CAR_DEALERSHIP_H

#include "car_points.h"
#include "car_zero_points.h"
#include "car_best_sells.h"
#include "car_sells.h"

class CarDealerShip{
    AVLTree<CarPoints> points;
    AVLTree<CarZeroPoints> zero_points;
    AVLTree<CarSells> sells;
    AVLTree<CarBestSells> best_sells;
};

#endif //DS_HW1_CAR_DEALERSHIP_H
