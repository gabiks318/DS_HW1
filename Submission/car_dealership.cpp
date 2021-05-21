#include <iostream>
#include "car_dealership.h"
#include "avl_tree.h"
#include "car_points.h"
#include "car_zero_points.h"
#include "car_best_sells.h"
#include "car_sells.h"
#include "exceptions.h"



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
        car_to_remove->removeCarType(points, best_sells);//mlogM + logn
        try {
            CarZeroPoints *zero_points_to_remove = zero_points.find(CarZeroPoints(car_to_remove->getTypeId(), 0));
            zero_points.remove(*zero_points_to_remove);//logn + mlogM
        }catch (NodeDoesntExist &e){
        }
        sells.remove(*car_to_remove);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (NodeDoesntExist &e) {
        return FAILURE;
    }
    return SUCCESS;
}
StatusType CarDealerShip::sellCar(int typeID, int modelID) { //7log + 4logM(m<M)
    if (typeID <= 0 || modelID < 0)
        return INVALID_INPUT;
    try {
        CarSells *car_to_sell = sells.find(CarSells(typeID, 0)); //logn
        if (car_to_sell->getNumOfModels() <= modelID) {
            return FAILURE;
        }
        //Update Best Seller Tree
        CarBestSells best_sells_copy = car_to_sell->getBestSellsCopy();
        car_to_sell->addSell(modelID);
        CarBestSells updated_car_best = car_to_sell->getBestSellsCopy();
        best_sells.remove(best_sells_copy); //logn
        best_sells.insert(updated_car_best); //logn

        this->updatePoints(typeID,modelID, 10);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (NodeDoesntExist &e) {
        return FAILURE;
    }
    return SUCCESS;
}


StatusType CarDealerShip::makeComplaint(int typeID, int modelID, int t) {
    if (typeID <= 0 || modelID < 0)
        return INVALID_INPUT;
    try{
    CarSells *car_to_complain = sells.find(CarSells(typeID, 0)); //logn
    if (car_to_complain->getNumOfModels() <= modelID) {
        return FAILURE;
    }

        this->updatePoints(typeID,modelID, -(int)100/t);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (NodeDoesntExist &e) {
        return FAILURE;
    }
    return SUCCESS;
}
void CarDealerShip::updatePoints(int typeID, int modelID, int add_points){

    CarSells *car_to_update = sells.find(CarSells(typeID, 0)); //logn
    CarZeroPoints *car_zero_ptr;

    try{
        car_zero_ptr = zero_points.find(CarZeroPoints(typeID, 0));
    } catch (NodeDoesntExist &e){
        car_zero_ptr = NULL;
    }


    // Car is inside zeroes tree
    if (car_to_update->getPoints(modelID) == 0) {

        car_zero_ptr->removeModel(modelID);//logm

        // Check if no more models with zero points of this car type, and delete tree if so
        if (car_zero_ptr->emptyModels()) {
            zero_points.remove(*car_zero_ptr);//logn
        }

        // Insert to points tree new object
        CarPoints new_car_points = CarPoints(typeID, modelID, add_points);
        points.insert(new_car_points);//logM

        // Update car pointers array with pointer to points tree (logM)
        car_to_update->setPoints(modelID, new_car_points.getPoints());

    } else {
        // Car is inside points tree
        CarPoints car_points_copy(typeID, modelID, car_to_update->getPoints(modelID));


        points.remove(car_points_copy);
        car_points_copy.updatePoints(add_points);

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
            car_to_update->setPoints(modelID, 0);
        } else {
            points.insert(car_points_copy);
            car_to_update->setPoints(modelID, car_points_copy.getPoints());
        }
    }
}


StatusType CarDealerShip::GetBestSellerModelByType(int typeID, int *modelID) {//typeid=0 1, else logn
    if (typeID < 0) {
        return INVALID_INPUT;
    }
    try {
        if(typeID == 0){
            if(sells.isEmpty()){ //1
                return FAILURE;
            }
            *modelID = best_sells.getMaxData()->getBestSellerModel(); //1
        } else {
            CarSells *car_sells = sells.find(CarSells(typeID, 0));
            CarBestSells best_sell_copy = car_sells->getBestSellsCopy();
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
    try {
        bool iterate_zero = false;
        bool negative_done = false;
        AVLTree<CarPoints>::AvlIterator points_iterator = points.begin();
        AVLTree<CarZeroPoints>::AvlIterator zero_tree_iterator = zero_points.begin();
        AVLTree<int>::AvlIterator zero_model_iterator = AVLTree<int>::AvlIterator(NULL, NULL);

        if(!zero_points.isEmpty()){
            zero_model_iterator = (*zero_tree_iterator)->getModels().begin();
        }
        if(points.isEmpty()) {
            iterate_zero = true;
            negative_done = true;
        }else if((*points_iterator)->getPoints() > 0){
            iterate_zero = true;
            negative_done = true;
        }

        for(int i = 0; i < numOfModels; i++){
            if(iterate_zero){
                if(zero_points.isEmpty()){
                    iterate_zero = false;
                    i--;
                    continue;
                }
                types[i] = (*zero_tree_iterator)->getTypeId();
                models[i] = *(*zero_model_iterator);
                ++zero_model_iterator;
                if(zero_model_iterator == (*zero_tree_iterator)->getModels().end()){
                    ++zero_tree_iterator;
                    if(zero_tree_iterator != zero_points.end()){
                        zero_model_iterator = (*zero_tree_iterator)->getModels().begin();
                    } else {
                        iterate_zero = false;
                    }
                }
            } else {
                types[i] = (*points_iterator)->getTypeId();
                models[i] = (*points_iterator)->getModel();
                ++points_iterator;
                if(!negative_done && (*points_iterator)->getPoints() > 0){
                    iterate_zero = true;
                    negative_done = true;
                }
            }
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
