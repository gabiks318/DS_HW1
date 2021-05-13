#ifndef DS_HW1_CAR_SELLS_H
#define DS_HW1_CAR_SELLS_H

#include "../AVL Tree/avl_tree.h"
#include "car_best_sells.h"
#include "car_points.h"

class CarSells{
private:
    int* models;
    int* models_points; // Keeps track of how many points the model has
//    CarPoints** model_ptr_arr;
//    CarBestSells* best_sells_ptr;
    int num_of_models;
    int type_id;
    int best_seller_amount;
    int best_seller_model;
public:
    CarSells(int type_id, int num_of_models);
    CarSells(const CarSells&);
    CarSells& operator=(const CarSells&);
    ~CarSells();
    bool operator<(const CarSells&) const;
    bool operator==(const CarSells&) const;
    int getNumOfModels() const;
    int getTypeId() const;

    int getBestSellerAmount() const;
    int getBestSellerModel() const;
    CarBestSells getBestSellsCopy() const;
//    void setBestSellsPtr(CarBestSells*);
//    CarBestSells* getBestSellsPtr() const;
    void setPoints(int model, int points);
    int getPoints(int model) const;
//    CarPoints* getCarPointsModel(int model) const;
//    void updatePointsPtr(int model, CarPoints* car_points_ptr);
    void removeCarType(AVLTree<CarPoints>& points_tree, AVLTree<CarBestSells>& best_sells);
    void addSell(int model);
};

bool operator>(const CarSells& car_sells1, const CarSells& car_sells2);

#endif //DS_HW1_CAR_SELLS_H
