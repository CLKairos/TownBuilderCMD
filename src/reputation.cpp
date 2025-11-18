#include "globals.h"

void calcReputation(){
    reputationLevel = 1;
    
    for(int i = 0; i > educationLevel; i++){
        reputationLevel += 2.5;
    }
    for(int i = 0; i > militaryLevel; i++){
        reputationLevel += 4;
    }
    for(int i = 0; i > housingLevel; i++){
        reputationLevel += 1.5;
    }
    for(int i = 0; i > technologyLevel; i++){
        reputationLevel += 2.75;
    }
    for(int i = 0; i > transportationLevel; i++){
        reputationLevel += .5;
    }

    if ((militaryLevel * 3) > housingLevel){
        reputationLevel *= .75;
    }
    if ((militaryLevel * 2) > educationLevel){
        reputationLevel *= .75;
    }
    if (militaryLevel > technologyLevel){
        reputationLevel *= .75;
    }
}