#include <iostream>
#include "car_dealership.h"
#include "../AVL Tree/avl_tree.h"
#include "../Car Classes/car_points.h"
#include "../Car Classes/car_zero_points.h"
#include "../Car Classes/car_best_sells.h"
#include "../Car Classes/car_sells.h"
#include "../AVL Tree/exceptions.h"



CarDealerShip::CarDealerShip() : points(), zero_points(), sells(), best_sells(), total_models(0) { // 1
}

StatusType CarDealerShip::AddCarType(int type_id, int num_of_models) { //5logn + 2m
    if (type_id <= 0 || num_of_models <= 0)
        return INVALID_INPUT;
    try {
        CarSells car_sells = CarSells(type_id, num_of_models);
        sells.insert(car_sells);//logn + m

        CarBestSells car_best_sells = CarBestSells(type_id);
        best_sells.insert(car_best_sells); //logn
        //saving the pointer of best sells
        CarSells *car_sells_ptr = sells.find(car_sells); //logn
        CarBestSells *car_best_sells_ptr = best_sells.find(car_best_sells); //logn
        car_sells_ptr->setBestSellsPtr(car_best_sells_ptr);

        zero_points.insert(CarZeroPoints(type_id, num_of_models)); //logn + m

    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (NodeExists &e) {
        return FAILURE;
    }
    total_models += num_of_models;
    return SUCCESS;
}

StatusType CarDealerShip::RemoveCarType(int type_id) { // 2mlogM + 3logn
    if (type_id <= 0)
        return INVALID_INPUT;
    try {
        CarSells *car_to_remove = sells.find(CarSells(type_id, 0));//logn
        total_models -= car_to_remove->getNumOfModels();
        car_to_remove->remove(points, best_sells);//mlogM + logn

        sells.remove(*car_to_remove);
        CarZeroPoints zero_points_copy = CarZeroPoints(car_to_remove->getTypeId(), 0);
        zero_points.remove(zero_points_copy);//logn + mlogM

    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (NodeDoesntExist &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType CarDealerShip::sellCar(int typeID, int modelID) { //7log + 4logM(m<M)
    if (typeID <= 0 || modelID <= 0)
        return INVALID_INPUT;
    try {
        CarSells *car_to_sell = sells.find(CarSells(typeID, 0)); //logn
        if (car_to_sell->getNumOfModels() <= modelID) {
            return INVALID_INPUT;
        }
        //Update Best Seller Tree
        car_to_sell->addSell(modelID);
        CarBestSells *best_sells_ptr = car_to_sell->getBestSellsPtr();
        best_sells_ptr->updateBestSeller(car_to_sell->getBestSellerAmount(), car_to_sell->getBestSellerModel());
        CarBestSells updated_car_best = CarBestSells(*best_sells_ptr);
        best_sells.remove(*best_sells_ptr); //logn
        best_sells.insert(updated_car_best); //logn

        this->updatePoints(typeID,modelID, 10);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CarDealerShip::makeComplaint(int typeID, int modelID, int t) {
    if (typeID <= 0 || modelID <= 0)
        return INVALID_INPUT;
    // TODO: check if modelID is in range(not more than max num)
    try{
        this->updatePoints(typeID,modelID, -(int)100/t);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void CarDealerShip::updatePoints(int typeID, int modelID, int add_points){
    CarSells *car_to_update = sells.find(CarSells(typeID, 0)); //logn
    CarPoints *car_points_ptr = car_to_update->getCarPointsModel(modelID);
    CarZeroPoints *car_zero_ptr = zero_points.find(CarZeroPoints(typeID, 0));

    // Car is inside zeroes tree
    if (car_points_ptr == NULL) {
        car_zero_ptr->removeModel(modelID);//logm

        // Check if no more models with zero points of this car type, and delete tree if so
        if (car_zero_ptr->emptyModels()) {
            zero_points.remove(*car_zero_ptr);//logn
        }

        // Insert to points tree new object
        CarPoints new_car_points = CarPoints(typeID, modelID, add_points);
        points.insert(new_car_points);//logM

        // Update car pointers array with pointer to points tree (logM)
        car_to_update->updatePointsPtr(modelID, points.find(new_car_points));


    } else {
        // Car is inside points tree

        car_points_ptr->updatePoints(add_points);
        CarPoints car_points_copy(*car_points_ptr);
        points.remove(*car_points_ptr);

        // If new score is 0, insert to zero tree
        if (car_points_copy.getPoints() == 0) {
            // If car type is not inside zero tree, create new tree
            if (car_zero_ptr == NULL) {
                zero_points.insert(CarZeroPoints(typeID, 0));//logn
                car_zero_ptr = zero_points.find(CarZeroPoints(typeID, 0)); //logn
            }
            //logn or 1 in case zero tree created
            car_zero_ptr->insertModel(modelID);
            // Update pointer to null in sells tree
            car_to_update->updatePointsPtr(modelID,NULL);
        } else {
            points.insert(car_points_copy);
            CarPoints* new_ptr = points.find(car_points_copy);
            car_to_update->updatePointsPtr(modelID, new_ptr);
        }
    }
}


StatusType CarDealerShip::GetBestSellerModelByType(int typeID, int *modelID) {//typeid=0 1, else logn
    if (typeID < 0) {
        return INVALID_INPUT;
    }
    try {
        if(modelID == 0){
            if(sells.isEmpty()){ //1
                return FAILURE;
            }
            *modelID = best_sells.getMaxData()->getBestSellerModel(); //1
        } else {
            CarBestSells best_sell_copy = CarBestSells(typeID);
            CarBestSells* best_sell_ptr = best_sells.find(best_sell_copy);//logn
            *modelID = best_sell_ptr->getBestSellerModel();
        }
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (NodeDoesntExist &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType CarDealerShip::GetWorstModels(int numOfModels, int *types, int *models) {
    if (numOfModels <= 0) {
        return INVALID_INPUT;
    }
    if(numOfModels> total_models){
        return FAILURE;
    }
    bool zero_done = false;
    int i = 0;
    try {
        for (AVLTree<CarPoints>::AvlIterator points_iterator = points.begin();
                        points_iterator != points.end(); ++points_iterator) {
            CarPoints *curr_points = *points_iterator;
            if (i >= numOfModels) break;
            if (!zero_done && curr_points->getPoints() > 0) { //done negative go to zeroes
                for (AVLTree<CarZeroPoints>::AvlIterator zero_iterator = zero_points.begin();
                                        zero_iterator != zero_points.end(); ++zero_iterator) {
                    CarZeroPoints *curr_zero_points = *zero_iterator;
                    AVLTree<int> &curr_zero_models = curr_zero_points->getModels();
                    for (AVLTree<int>::AvlIterator zero_model_iterator = curr_zero_models.begin();
                                    zero_model_iterator != curr_zero_models.end(); ++zero_model_iterator) {
                        if (i >= numOfModels) break;
                        types[i] = curr_zero_points->getTypeId();
                        models[i] = *(*zero_model_iterator);
                        i++;
                    }
                    if (i >= numOfModels) break;
                }
                zero_done = true;
            } else {
                types[i] = curr_points->getTypeId();
                models[i] = curr_points->getModel();
            }
            i++;
        }
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void CarDealerShip::Quit() {
    points.empty();
    zero_points.empty();
    sells.empty();
    best_sells.empty();
}
