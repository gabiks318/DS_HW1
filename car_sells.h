#ifndef DS_HW1_CAR_SELLS_H
#define DS_HW1_CAR_SELLS_H

#include "avl_tree.h"
#include "car_best_sells.h"

class CarSells{
private:
    int* models;
    int num_of_models;
    int type_id;
    int best_seller_amount;
    int best_seller_model;
public:
    CarSells(int type_id, int num_of_models, CarBestSells* best_sells_ptr);
    ~CarSells();
    bool operator<(const CarSells&) const;
    bool operator==(const CarSells&) const;
    int getNumOfModels() const;
    int getTypeId() const;
    int getBestSellerAmount() const;
    int getBestSellerModel() const;
    void addSell(int model);
};

bool operator>(const CarSells& car_sells1, const CarSells& car_sells2);

#endif //DS_HW1_CAR_SELLS_H
