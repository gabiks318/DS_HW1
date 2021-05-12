#include "library.h"
#include "car_dealership.h"

void* Init(){
    CarDealerShip *DS = new CarDealerShip();
    return (void*)DS;
}

StatusType AddCarType(void *DS, int typeID, int numOfModels) {
    if(DS == NULL) return INVALID_INPUT;
    return ((CarDealerShip*)DS)-> AddCarType(typeID, numOfModels);
}
StatusType RemoveCarType(void *DS, int typeID){
    if(DS == NULL) return INVALID_INPUT;
    return ((CarDealerShip*)DS)-> RemoveCarType(typeID);
}

StatusType makeComplaint(void *DS, int typeID, int modelID, int t){
    if(DS == NULL) return INVALID_INPUT;
    return ((CarDealerShip*)DS)-> makeComplaint(typeID, modelID, t);
}

StatusType GetBestSellerModelByType(void *DS, int typeID, int * modelID){
    if(DS == NULL) return INVALID_INPUT;
    return ((CarDealerShip*)DS)-> GetBestSellerModelByType(typeID,modelID));
}

StatusType GetWorstModels(void *DS, int numOfModels, int *types, int *models){
    if(DS == NULL) return INVALID_INPUT;
    return ((CarDealerShip*)DS)-> GetWorstModels(numOfModels,types,models);
}

void Quit(void** DS){
    *DS = ((CarDealerShip*)DS)-> Quit();
}
