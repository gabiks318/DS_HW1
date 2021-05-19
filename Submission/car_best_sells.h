#ifndef DS_HW1_CAR_BEST_SELLS_H
#define DS_HW1_CAR_BEST_SELLS_H

#include "avl_tree.h"

class CarBestSells {
private:
    int type_id;
    int best_seller_amount;
    int best_seller_model;
public:
    CarBestSells(int typeId);
    ~CarBestSells() = default;
    CarBestSells(const CarBestSells&);
    CarBestSells& operator=(const CarBestSells&);
    void updateBestSeller(int best_seller_amount, int best_seller_model);
    bool operator<(const CarBestSells&) const;
    bool operator==(const CarBestSells&) const;
    int getBestSellerAmount() const;
    int getBestSellerModel() const;
    int getTypeId() const;
};

bool operator>(const CarBestSells& car_sells1, const CarBestSells& car_sells2);

#endif //DS_HW1_CAR_BEST_SELLS_H
