#ifndef DS_HW1_CAR_DEALERSHIP_H
#define DS_HW1_CAR_DEALERSHIP_H

#include "car_points.h"
#include "car_zero_points.h"
#include "car_best_sells.h"
#include "car_sells.h"
#include "library.h"

class CarDealerShip{
private:
    AVLTree<CarPoints> points; // Points Tree
    AVLTree<CarZeroPoints> zero_points; // Car Type tree, each node is another tree
    AVLTree<CarSells> sells; // Car Type tree
    AVLTree<CarBestSells> best_sells; // Sales tree
    int total_models;

public:
    CarDealerShip();
    ~CarDealerShip() = default;
    StatusType AddCarType(int type_id, int num_of_models);
    StatusType RemoveCarType(int type_id);
    StatusType sellCar(int typeID, int modelID);
    StatusType makeComplaint(int typeID, int modelID, int t);
    StatusType GetBestSellerModelByType(int typeID, int * modelID);
    StatusType GetWorstModels(int numOfModels, int *types, int *models);
    void updatePoints(int typeID, int modelID, int add_points);
    void Quit();
    };


#endif //DS_HW1_CAR_DEALERSHIP_H
