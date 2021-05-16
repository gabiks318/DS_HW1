#include "car_points.h"

CarPoints::CarPoints(int type_id, int model, int points): type_id(type_id), model(model), points(points) {
}
CarPoints::CarPoints(const CarPoints& car_points): type_id(car_points.type_id), model(car_points.model),
    points(car_points.points){
}

CarPoints& CarPoints::operator=(const CarPoints& car_points){
    if(this == &car_points){
        return *this;
    }
    type_id = car_points.type_id;
    model = car_points.model;
    points = car_points.points;
    return *this;
}

void CarPoints::updatePoints(int updated_points) {
    points += updated_points;
}

int CarPoints::getPoints() const {
    return points;
}

int CarPoints::getModel() const {
    return model;
}
int CarPoints::getTypeId() const {
    return type_id;
}

bool CarPoints::operator<(const CarPoints& car_points) const {
    if(points != car_points.getPoints())
        return points < car_points.getPoints();
    if(type_id != car_points.getTypeId())
        return type_id < car_points.getTypeId();
    return model < car_points.getModel();
}

bool CarPoints::operator==(const CarPoints& car_points) const{
    return type_id == car_points.type_id && model == car_points.model;
}

bool operator>(const CarPoints& car_points1, const CarPoints& car_points2){
    return car_points2 < car_points1;
}



