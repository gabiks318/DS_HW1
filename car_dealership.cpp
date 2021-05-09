#include "car_dealership.h"
#include "avl_tree.h"
#include "car_points.h"
#include "car_zero_points.h"
#include "car_best_sells.h"
#include "car_sells.h"
#include "exceptions.h"

CarDealerShip::CarDealerShip(): points(), zero_points(), sells(), best_sells(){ // 1
}

StatusType CarDealerShip::AddCarType(int type_id, int num_of_models){ //5logn + 2m
    if(type_id <= 0 || num_of_models <= 0)
        return INVALID_INPUT;
    try {
        CarSells car_sells = CarSells(type_id, num_of_models);
        sells.insert(car_sells);//logn + m

        CarBestSells car_best_sells = CarBestSells(type_id);
        best_sells.insert(car_best_sells); //logn
        //saving
        CarSells* car_sells_ptr = find(car_sells); //logn
        CarBestSells* car_best_sells_ptr = find(car_best_sells); //logn
        car_sells_ptr->setBestSellsPtr(car_best_sells_ptr);

        zero_points.insert(CarZeroPoints(type_id, num_of_models)); //logn + m

    } catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    } catch(NodeExists& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType CarDealerShip::RemoveCarType(int type_id){ // 2mlogM + 3logn
    if(type_id <= 0)
        return INVALID_INPUT;
    try {
        CarSells* car_to_remove = sells.find(CarSells(type_id,0));//logn
        car_to_remove->remove(points, best_sells);//mlogM + logn

        zero_points.remove(*car_to_remove);//logn + mlogM
        sells.remove(*car_to_remove);

    } catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    } catch(NodeDoesntExists& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType CarDealerShip::sellCar(int typeID, int modelID){ //7log + 4logM(m<M)
    if(type_id <= 0 || num_of_models <= 0)
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

        CarPoints *car_points = car_to_sell->getCarPointsModel(modelID);
        CarZeroPoints *car_zero_ptr = zero_points.find(CarZeroPoints(typeID, 0));
        if (car_points == NULL) {// the car is inside zeroes tree
            car_zero_ptr->removeModel(modelID); //logm
            if (car_zero_ptr->emptyModels()) { //no more models with zero rank from this type
                zero_points.remove(&car_zero_ptr); //logn + logm
            }
            CarPoints car_points = CarPoints(typeID, modelID, 10);
            points.insert(car_points);//logM
            car_to_sell->updatePointsPtr(modelID, car_points.find(
                    car_points)); //logM update car pointers arr that this model moved to points tree
        } else { //the car is inside points tree
            car_points->updatePoints(10);
            if (car_points->getPoints() == 0) {// put it back in zeroes tree
                if (car_zero_ptr == NULL) { //this type isn't inside zeroes tree
                    zero_points.insert(CarZeroPoints(typeID, 0));//logn
                    car_zero_ptr = zero_points.find(CarZeroPoints(typeID, 0)); //logn
                    car_zero_ptr->insertModel(modelID); //1
                } else {
                    car_zero_ptr->insertModel(modelID); //logn
                }
                car_to_sell->updatePointsPtr(modelID,NULL); //update car pointers arr that this model moved to zeroes tree
            }
            else{
                CarPoints updated_points_car = CarPoints(*car_points);
                car_points.remove(*car_points);
                car_points.insert(updated_points_car)
            }
        }
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CarDealerShip::makeComplaint(int typeID, int modelID, int t){

}

StatusType CarDealerShip::GetBestSellerModelByType(int typeID, int * modelID){

}

StatusType CarDealerShip::GetWorstModels(int numOfModels, int *types, int *models){

}

void CarDealerShip::Quit(){

}

