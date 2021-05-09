#include "car_sells.h"
#include "car_best_sells.h"
#include "car_points.h"

CarSells::CarSells(int type_id, int num_of_models):
    models(new int[num_of_models]), model_ptr_arr(new *CarBestSells[num_of_models]), best_sells_ptr(NULL),
    num_of_models(num_of_models), type_id(type_id), best_seller_amount(0), best_seller_model(0){
    for(int model=0; model<num_of_models; model++) {
        models[model] = model;
        model_ptr_arr[model] = NULL;
    }
}

CarSells(const CarSells&);
CarSells operator=(const CarSells&);
CarSells::~CarSells(){
    delete [] models;
    delete [] model_ptr_arr
}

void CarSells::setBestSellsPtr(CarBestSells* ptr){
    best_sells_ptr = ptr;
}

void CarSells::remove(AVLTree<CarPoints>& points_tree, AVLTree<CarBestSells>& best_sells){
    for(int model=0; model<num_of_models; model++){ //mlogM
        if(model_ptr_arr[model] != NULL) {
            points_tree.remove(*model_ptr_arr[model]);
        }
    }
    best_sells.remove(*best_sells_ptr); //logn
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