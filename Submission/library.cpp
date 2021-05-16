#include "library.h"
#include "car_dealership.h"

void* Init(){
    CarDealerShip *DS = new CarDealerShip();
    return static_cast<void*>(DS);
}

StatusType AddCarType(void *DS, int typeID, int numOfModels) {
    if(DS == NULL) return INVALID_INPUT;
    return static_cast<CarDealerShip*>(DS)-> AddCarType(typeID, numOfModels);
}

StatusType RemoveCarType(void *DS, int typeID){
    if(DS == NULL) return INVALID_INPUT;
    return static_cast<CarDealerShip*>(DS)-> RemoveCarType(typeID);
}
StatusType SellCar(void *DS, int typeID, int modelID){
    if(DS == NULL) return INVALID_INPUT;
    return static_cast<CarDealerShip*>(DS)-> sellCar(typeID, modelID);
}

StatusType MakeComplaint(void *DS, int typeID, int modelID, int t){
    if(DS == NULL) return INVALID_INPUT;
    return static_cast<CarDealerShip*>(DS)-> makeComplaint(typeID, modelID, t);
}

StatusType GetBestSellerModelByType(void *DS, int typeID, int * modelID){
    if(DS == NULL) return INVALID_INPUT;
    return static_cast<CarDealerShip*>(DS)-> GetBestSellerModelByType(typeID,modelID);
}

StatusType GetWorstModels(void *DS, int numOfModels, int *types, int *models){
    if(DS == NULL) return INVALID_INPUT;
    return static_cast<CarDealerShip*>(DS)-> GetWorstModels(numOfModels,types,models);
}

void Quit(void** DS){
    CarDealerShip *to_destroy = static_cast<CarDealerShip*>(*DS);
    to_destroy-> Quit();
    delete to_destroy;
    *DS = NULL;
}
