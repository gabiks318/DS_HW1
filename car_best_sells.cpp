#include "car_best_sells.h"

CarBestSells::CarBestSells(int type_id):type_id(type_id),best_seller_amount(best_seller_amount),
                                        best_seller_model(best_seller_model){

}

void CarBestSells::updateBestSeller(int updated_best_seller_amount, int updated_best_seller_model) {
    best_seller_model = updated_best_seller_model;
    best_seller_amount = updated_best_seller_amount;
}

bool CarBestSells::operator<(const CarBestSells& car_best_sells) const {
    if(best_seller_amount != car_best_sells.getBestSellerAmount())
        return !(best_seller_amount < car_best_sells.getBestSellerAmount());
    if(best_seller_amount != car_best_sells.getBestSellerAmount())
        return type_id < car_sells.getTypeId();
    return best_seller_model < car_best_sells.getBestSellerModel();

}

bool CarBestSells::operator==(const CarBestSells& car_best_sells) const{
    return type_id == car_best_sells.getTypeId();
}


bool operator>(const CarBestSells& car_best_sells1, const CarBestSells& car_best_sells2){
    return car_best_sells2 < car_best_sells1;
}

int getTypeId() const{
    return type_id;
}

int getBestSellerAmount() const{
    return best_seller_amount;
}

int getBestSellerModel() const{
    return best_seller_model;
}
