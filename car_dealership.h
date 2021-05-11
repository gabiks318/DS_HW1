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
    class PrintWorst{
        int* types;
        int* models;
        int* index;
        int limit;
        int mode; // Takes -1,0,1 to indicate mode

    public:
        PrintWorst(int* types, int* models, int limit, int* index):types(types), models(models), index(index), limit(limit), mode(0){};
        bool operator()(CarPoints* car_points);
        void setNegative();
        void setPositive();
        bool isFinished();
        void updatePoints(int typeID, int modelID, int points);
    };

    class PrintWorstZero{
        int* types;
        int* models;
        int* index;
        int limit;

    public:
        PrintWorstZero(int* types, int* models, int limit, int* index):types(types), models(models), index(index), limit(limit){};
        bool operator()(CarZeroPoints* car_points);
        class PrintZeroAux{
            int* types;
            int* models;
            int* index;
            int limit;
            int car_type;
        public:
            PrintZeroAux(int* types, int* models, int limit, int* index. int car_type):types(types), models(models), index(index), limit(limit), car_type(car_type){};
        };
    };

public:
    CarDealerShip();
    ~CarDealerShip() = default;
    StatusType AddCarType(int type_id, int num_of_models);
    StatusType RemoveCarType(int type_id);
    StatusType sellCar(int typeID, int modelID);
    StatusType makeComplaint(int typeID, int modelID, int t);
    StatusType GetBestSellerModelByType(int typeID, int * modelID);
    StatusType GetWorstModels(int numOfModels, int *types, int *models);
    void Quit();

};

#endif //DS_HW1_CAR_DEALERSHIP_H
