#include "car_sells.h"

CarSells::CarSells(int type_id, int num_of_models, CarBestSells* best_sells_ptr):models(new int[num_of_models]),
                                                                       num_of_models(num_of_models), type_id(type_id), best_seller_amount(0), best_seller_model(0){
    for(int i=0; i<m; i++)
        models[i] = i;
}

CarSells::~CarSells(){
    delete [] models;
}

void CarSells::addSell(int model){ //assume model<num_of_models
    models[model]++;
    if(models[model] == best_seller_amount){
        best_seller_model = model < best_seller_model ? model : best_seller_model;
    }
    else if(models[model] > best_seller_amount){
        best_seller_model = model;
        best_seller_amount = models[model];
    }
}

bool CarSells::operator<(const CarSells& car_sells) const{
    return type_id < car_sells.getTypeId();
}

bool CarSells::operator==(const CarSells&) const{
    return type_id == car_sells.getTypeId();
}

bool operator>(const CarSells& car_sells1, const CarSells& car_sells2){
    return car_sells2 < car_sells1;
}

int CarSells::getNumOfModels() const{
    return num_of_models;
}
int CarSells::getTypeId() const{
    return type_id;
}
int CarSells::getBestSellerAmount() const{
    return best_seller_amount;
}
int CarSells::getBestSellerModel() const{
    return best_seller_model;
}