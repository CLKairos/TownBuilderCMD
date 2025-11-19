#include "globals.h"
#include "reputation.h"
#include <iostream>

void calcReputation(){    
    int eLvl;
    int mLvl;
    int hLvl;
    int teLvl;
    int trLvl;
    
    if (eLvl == educationLevel && mLvl == militaryLevel && hLvl == housingLevel && teLvl == technologyLevel && trLvl == transportationLevel){
        reputationLevel = reputationLevel;
    }
    else {
        reputationLevel = 0;

        for(int i = 0; i < educationLevel; i++){
            reputationLevel += 2.5;
            eLvl = educationLevel;
        }
        for(int i = 0; i < militaryLevel; i++){
            reputationLevel += 4;
            mLvl = militaryLevel;
        }
        for(int i = 0; i < housingLevel; i++){
            reputationLevel += 1.5;
            hLvl = housingLevel;
        }
        for(int i = 0; i < technologyLevel; i++){
            reputationLevel += 2.75;
            teLvl = technologyLevel;
        }
        for(int i = 0; i < transportationLevel; i++){
            reputationLevel += .5;
            trLvl = transportationLevel;
        }

        if ((militaryLevel * 3) > housingLevel){
            reputationLevel *= .75;
        }
        else if ((militaryLevel * 2) > educationLevel){
            reputationLevel *= .75;
        }
        else if (militaryLevel > technologyLevel){
            reputationLevel *= .75;
        }
    }
}