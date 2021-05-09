#include "car_dealership.h"
#include "avl_tree.h"
#include "car_points.h"
#include "car_zero_points.h"
#include "car_best_sells.h"
#include "car_sells.h"
#include "exceptions.h"

CarDealerShip::CarDealerShip(): points(), zero_points(), sells(), best_sells(){
}

StatusType CarDealerShip::AddCarType(int type_id, int num_of_models){ //5logn + 2m
    if(type_id <= 0 || num_of_models <= 0)
        return INVALID_INPUT;
    try {
        CarSells car_sells = CarSells(type_id, num_of_models);
        sells.insert(car_sells);//logn + m

        CarBestSells car_best_sells = CarBestSells(type_id);
        best_sells.insert(car_best_sells); //logn

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

StatusType CarDealerShip::RemoveCarType(int type_id){
    if(type_id <= 0)
        return INVALID_INPUT;
    try {
        CarSells* car_to_remove = sells.find(CarSells(type_id,0));//logn
        car_to_remove->remove(points, best_sells);//mlogM + logn

        zero_points.remove(*car_to_remove);//logn + mlogm
        sells.remove(*car_to_remove);

    } catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    } catch(NodeDoesntExists& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType CarDealerShip::sellCar(int typeID, int modelID){

}

StatusType CarDealerShip::makeComplaint(int typeID, int modelID, int t){

}

StatusType CarDealerShip::GetBestSellerModelByType(int typeID, int * modelID){

}

StatusType CarDealerShip::GetWorstModels(int numOfModels, int *types, int *models){

}

void CarDealerShip::Quit(){

}

