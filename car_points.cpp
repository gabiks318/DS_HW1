#include "car_points.h"

CarPoints::CarPoints(int type_id, int model, int points): type_id(type_id), model(model), points(points) {
}

void CarPoints::updatePoints(int updated_points) {
    points = updated_points;
}

int CarPoints::getPoint() const {
    return points;
}

int CarPoints::getModel() const {
    return model;
}
int CarPoints::getTypeId() const {
    return type_id;
}

bool CarPoints::operator<(const CarPoints& car_points) const {
    if(points != car_points.getpoints())
        return !(points < car_points.getpoints());
    if(type_id != car_best_sells.getTypeId())
        return type_id < car_sells.getTypeId();
    return model < car_points.getModel();
}

bool CarPoints::operator==(const CarPoints& car_points) const{
    return type_id == car_points.getTypeId();
}

bool operator>(const CarPoints& car_points1, const CarPoints& car_points2){
    car_points2 < car_points1;
}



