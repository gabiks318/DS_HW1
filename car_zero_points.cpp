#include "car_zero_points.h"
#include "avl_tree.h"

CarZeroPoints::CarZeroPoints(int type_id, int num_of_models): models(), type_id(type_id) {
    int* models_arr = new int[num_of_models];
    for(int model = 0; model < num_of_models; model++)
        models_arr[model] = model;
    models.SortedArrayInit(models_arr, num_of_models);
    delete [] models_arr;
}

CarZeroPoints::~CarZeroPoints(){
    models.empty();
}

bool CarZeroPoints::operator<(const CarZeroPoints& car_zero_points) const {
    return type_id < car_zero_points.getTypeId();
}

bool CarZeroPoints::operator==(const CarZeroPoints& car_zero_points) const {
    return type_id == car_zero_points.getTypeId();
}

bool operator>(const CarZeroPoints& car_zero_points1, const CarZeroPoints& car_zero_points2){
    return car_zero_points2<car_zero_points1;
}

int CarZeroPoints::getTypeId() const{
    return type_id;
}

AVLTree<int>& CarZeroPoints::getModels() const{
    return models;
}

