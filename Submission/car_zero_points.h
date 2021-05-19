#ifndef DS_HW1_CAR_ZERO_POINTS_H
#define DS_HW1_CAR_ZERO_POINTS_H

#include "avl_tree.h"

class CarZeroPoints{
private:
    AVLTree<int> models;
    int type_id;
public:
    CarZeroPoints(int type_id, int num_of_models);
    ~CarZeroPoints();
    CarZeroPoints(const CarZeroPoints&);
    CarZeroPoints& operator=(const CarZeroPoints&);
    bool operator<(const CarZeroPoints&) const;
    bool operator==(const CarZeroPoints&) const;
    void insertModel(int model);
    void removeModel(int model);
    int getTypeId() const;
    bool emptyModels() const;
    AVLTree<int>& getModels();
};
bool operator>(const CarZeroPoints& car_zero_points1, const CarZeroPoints& car_zero_points2);

#endif //DS_HW1_CAR_ZERO_POINTS_H
