#include "car_best_sells.h"

CarBestSells::CarBestSells(int type_id):type_id(type_id),best_seller_amount(0),best_seller_model(0){

}
CarBestSells::CarBestSells(const CarBestSells& car_sells):type_id(car_sells.type_id),best_seller_amount(car_sells.best_seller_amount),
        best_seller_model(car_sells.best_seller_model){

}

CarBestSells& CarBestSells::operator=(const CarBestSells& car_sells){
    if(this == &car_sells){
        return *this;
    }
    type_id = car_sells.type_id;
    best_seller_amount = car_sells.best_seller_amount;
    best_seller_model = car_sells.best_seller_model;
    return *this;
}

void CarBestSells::updateBestSeller(int updated_best_seller_amount, int updated_best_seller_model) {
    best_seller_model = updated_best_seller_model;
    best_seller_amount = updated_best_seller_amount;
}

bool CarBestSells::operator<(const CarBestSells& car_best_sells) const {
    if(best_seller_amount != car_best_sells.best_seller_amount)
        return best_seller_amount < car_best_sells.best_seller_amount;
    if(type_id != car_best_sells.type_id)
        return type_id > car_best_sells.getTypeId();
    return best_seller_model > car_best_sells.best_seller_model;

}

bool CarBestSells::operator==(const CarBestSells& car_best_sells) const{
    return type_id == car_best_sells.type_id;
}


bool operator>(const CarBestSells& car_best_sells1, const CarBestSells& car_best_sells2){
    return car_best_sells2 < car_best_sells1;
}

int CarBestSells::getTypeId() const{
    return type_id;
}

int CarBestSells::getBestSellerAmount() const{
    return best_seller_amount;
}

int CarBestSells::getBestSellerModel() const{
    return best_seller_model;
}
