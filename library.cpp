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

