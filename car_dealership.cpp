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
        //saving the pointer of best sells
        CarSells *car_sells_ptr = find(car_sells); //logn
        CarBestSells *car_best_sells_ptr = find(car_best_sells); //logn
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
        car_to_remove->remove(points, best_sells);//mlogM + logn

        zero_points.remove(*car_to_remove);//logn + mlogM
        sells.remove(*car_to_remove);

    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (NodeDoesntExists &e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType CarDealerShip::sellCar(int typeID, int modelID) { //7log + 4logM(m<M)
    if (type_id <= 0 || num_of_models <= 0)
        return INVALID_INPUT;
    try {
        CarSells *car_to_sell = sells.find(CarSells(type_id, 0)); //logn
        if (car_to_sell->getNumOfModels() <= modelID) {
            return INVALID_INPUT;
        }
        //Update Best Seller Tree
        car_to_sell->addSell(modelId);
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
    if (type_id <= 0 || num_of_models <= 0)
        return INVALID_INPUT;
    try{
        this->updatePoints(typeID,modelID, -(int)100/t);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void CarDealerShip::updatePoints(int typeID, int modelID, int points){
    CarSells *car_to_update = sells.find(CarSells(type_id, 0)); //logn
    CarPoints *car_points = car_to_update->getCarPointsModel(modelID);
    CarZeroPoints *car_zero_ptr = zero_points.find(CarZeroPoints(typeID, 0));
    if (car_points == NULL) {// the car is inside zeroes tree
        car_zero_ptr->removeModel(modelID);//logm
        if (car_zero_ptr->emptyModels()) { //no more models with zero rank from this type
            zero_points.remove(*car_zero_ptr);//logn
        }
        CarPoints car_points = CarPoints(typeID, modelID, points);
        points.insert(car_points);//logM
        car_to_update->updatePointsPtr(modelID, car_points.find(
                car_points)); //logM update car pointers arr that this model moved to points tree
    } else { //the car is inside points tree
        car_points->updatePoints(points);
        if (car_points->getPoints() == 0) {// put it back in zeroes tree
            if (car_zero_ptr == NULL) { //this type isn't inside zeroes tree
                zero_points.insert(CarZeroPoints(typeID, 0));//logn
                car_zero_ptr = zero_points.find(CarZeroPoints(typeID, 0)); //logn
                car_zero_ptr->insertModel(modelID); //1
            } else {
                car_zero_ptr->insertModel(modelID); //logn
            }
            car_to_update->updatePointsPtr(modelID,
                                             NULL); //update car pointers arr that this model moved to zeroes tree
        } else {
            CarPoints updated_points_car = CarPoints(*car_points);
            car_points.remove(*car_points);
            car_points.insert(updated_points_car);
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
    } catch (NodeDoesntExists &e) {
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
            CarPoints &curr_points = *points_iterator;
            if (i >= numOfModels) break;
            if (!zero_done && curr.getPoints() > 0) { //done negative go to zeroes
                for (AVLTree<CarZeroPoints>::AvlIterator zero_iterator = zero_points.begin();
                                        zero_iterator != zero_points.end(); ++zero_iterator) {
                    CarZeroPoints &curr_zero_points = *zero_iterator;
                    AVLTree<int> &curr_zero_models = curr_zero_points.getModels();
                    for (AVLTree<int>::AvlIterator zero_model_iterator = curr_zero_models.begin();
                                    zero_model_iterator != curr_zero_models.end(); ++zero_model_iterator) {
                        if (i >= numOfModels) break;
                        types[i] = curr_zero_points.getTypeId();
                        models[i] = *zero_model_iterator;
                        i++;
                    }
                    if (i >= numOfModels) break;
                }
                zero_done = true;
            } else {
                types[i] = curr.getTypeId();
                models[i] = curr.getModel();
            }
            i++;
        }
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


/*
StatusType CarDealerShip::GetWorstModels(int numOfModels, int *types, int *models) {
    if (numOfModels <= 0) {
        return INVALID_INPUT;
    }
    if(numOfModels> total_models){
        return FAILURE;
    }
    try {
    // Initiate predicate, set to negative points
    int index = 0;
    PrintWorst predicate = PrintWorst(types, models, numOfModels, &index);
    PrintWorstZero predicate_zero = PrintWorstZero(types, models, numOfModels, &index);
    predicate.setNegative();
    points.iterate(predicate);
    if(!predicate.isFinished()){
        zero_points.iterate(predicate_zero);
        if(!predicate.isFinished()){
            predicate.setPositive();
            points.iterate_continue(predicate);
        }
    }
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}
*/
void CarDealerShip::Quit() {
    points.empty();
    zero_points.empty();
    sells.empty();
    best_sells.empty();
}
/*
bool CarDealership::PrintWorst::operator()(CarPoints *car_points) {
    // Check if limit was reached
    if(*index == limit)
        return false;
    // If positive mode, check if points are positive
    if(mode > 0){
        if(car_points->getPoints() <= 0)
            return false;
    } else if(mode < 0){
        // If negative mode, check if points are negative
        if(car_points->getPoints() >= 0)
            return false;
    }

    // If all checks passed, add model and type to array
    types[*index] = car_points->getTypeId();
    models[*index] = car_points->getModel();
    (*index)++;
    return true;
}

void CarDealership::PrintWorst::setNegative(){
    mode = -1;
}

void CarDealership::PrintWorst::setPositive(){
    mode = 1;
}

bool CarDealership::PrintWorst::isFinished(){
    return index == limit;
}
bool CarDealership::PrintWorstZero::operator()(CarZeroPoints *car_points) {
    // Check if limit was reached
    if(*index == limit)
        return false;
    PrintZeroAux predicate_helper = PrintZeroAux(types, models, limit, index, car_points->getTypeId());
    AVLTree<int> model_tree = car_points->getModels();
    model_tree.iterate(predicate_helper);
    // Check again, iteration might have stopped before all tree was traversed
    if(*index == limit)
        return false;
    return true;
}

bool CarDealership::PrintWorstZero::PrintZeroAux::operator()(int *model_num){
    // Check if limit was reached
    if(*index == limit)
        return false;

    types[*index] = car_type;
    models[*index] = *model_num;
    (*index)++;
    return true
}*/