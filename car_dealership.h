#ifndef DS_HW1_CAR_DEALERSHIP_H
#define DS_HW1_CAR_DEALERSHIP_H

#include "car_points.h"
#include "car_zero_points.h"
#include "car_best_sells.h"
#include "car_sells.h"
#include "library.h"

class CarDealerShip{
private:
    AVLTree<CarPoints> points;
    AVLTree<CarZeroPoints> zero_points;
    AVLTree<CarSells> sells;
    AVLTree<CarBestSells> best_sells;

    class PrintPositive{
    public:
        bool operator()(CarPoints* car_points);
    };

    class PrintNegative{
    public:
        bool operator()(CarPoints* car_points);
    };

public:
    CarDealerShip();
    Statupe_id, int num_of_models);
    StatusType RemoveCarType(int type_id);
    StatusType sellCar(int typeID, int modelID);
    StatusType makeComplaint(int typeID, int modelID, int t);
    StatusType GetBestSellerModelByType(int typeID, int * modelID);
    StatusType GetWorstModels(int numOfModels, int *types, int *models);
    void Quit();

};

#endif //DS_HW1_CAR_DEALERSHIP_H
