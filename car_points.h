#ifndef DS_HW1_CAR_POINTS_H
#define DS_HW1_CAR_POINTS_H

#include "avl_tree.h"

class CarPoints{
private:
    int type_id;
    int model;
    int points;
public:
    CarPoints(int type_id, int model, int points);
    ~CarPoints() = default;
    CarPoints(const CarPoints&);
    CarPoints& operator=(const CarPoints&);
    void updatePoints(int points);
    int getPoints() const;
    int getModel() const;
    int getTypeId() const;
    bool operator<(const CarPoints&) const;
    bool operator==(const CarPoints&) const;
};
bool operator>(const CarPoints& car_points1, const CarPoints& car_points2);


#endif //DS_HW1_CAR_POINTS_H
