#include "car_sells.h"

CarSells::CarSells(int type_id, int num_of_models):
        models(new int[num_of_models]), models_points(new int[num_of_models]),
        num_of_models(num_of_models), type_id(type_id), best_seller_amount(0), best_seller_model(0){
    for(int model=0; model<num_of_models; model++) {
        models[model] = 0;
        models_points[model] = 0;
    }
}

CarSells::CarSells(const CarSells& car_sells):
        models(new int[car_sells.num_of_models]), models_points(new int[car_sells.num_of_models]),
        num_of_models(car_sells.num_of_models), type_id(car_sells.type_id),
        best_seller_amount(car_sells.best_seller_amount), best_seller_model(car_sells.best_seller_model){
    for(int model=0; model<num_of_models; model++) {
        models[model] = car_sells.models[model];
        models_points[model] = car_sells.models_points[model];
    }
}

CarSells& CarSells::operator=(const CarSells& car_sells){
    if(this == &car_sells){
        return *this;
    }
    for(int model=0; model<num_of_models; model++) {
        models[model] = car_sells.models[model];
        models_points[model] = car_sells.models_points[model];
    }
    num_of_models = car_sells.num_of_models;
    type_id = car_sells.type_id;
    best_seller_amount = car_sells.best_seller_amount;
    best_seller_model = car_sells.best_seller_model;
    return *this;
}

CarSells::~CarSells(){
    delete [] models;
    delete [] models_points;
}

void CarSells::setPoints(int model, int points){
    models_points[model] = points;
}
int CarSells::getPoints(int model) const{
    return models_points[model];
}

void CarSells::removeCarType(AVLTree<CarPoints>& points_tree, AVLTree<CarBestSells>& best_sells){
    for(int model=0; model<num_of_models; model++){ //mlogM
        if(models_points[model] != 0) {
            points_tree.remove(CarPoints(type_id, model, models_points[model]));
        }
    }
    CarBestSells best_sells_copy = getBestSellsCopy();
    best_sells.remove(best_sells_copy); //logn
}
CarBestSells CarSells::getBestSellsCopy() const {
    CarBestSells best_sells_copy = CarBestSells(type_id);
    best_sells_copy.updateBestSeller(best_seller_amount, best_seller_model);
    return best_sells_copy;
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
    return type_id < car_sells.type_id;
}

bool CarSells::operator==(const CarSells& car_sells) const{
    return type_id == car_sells.type_id;
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

