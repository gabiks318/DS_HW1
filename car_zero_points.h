#ifndef DS_HW1_CAR_ZERO_POINTS_H
#define DS_HW1_CAR_ZERO_POINTS_H

#include "avl_tree.h"

class CarZeroPoints{
private:
    AVLTree<int> models;
    int type_id;
public:
    CarZeroPoints(int type_id, int num_of_models);//build tree with algorithm
    ~CarZeroPoints();
    bool operator<(const CarZeroPoints&) const;
    bool operator==(const CarZeroPoints&) const;
    int getTypeId() const;
};
bool operator>(const CarZeroPoints& car_zero_points1, const CarZeroPoints& car_zero_points2);

#endif //DS_HW1_CAR_ZERO_POINTS_H
