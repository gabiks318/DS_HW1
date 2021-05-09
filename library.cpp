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

    return ((CarDealerShip*)DS)-> makeComplaint(typeID);
}

StatusType GetBestSellerModelByType(void *DS, int typeID, int * modelID){

}

StatusType GetWorstModels(void *DS, int numOfModels, int *types, int *models){

}

void Quit(void** DS){

}
