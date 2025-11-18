#include <cstdlib>
#include <algorithm>
#include "globals.h"
#include "growth.h"
#include "housing.h"
using namespace std;

//population growth logic, based on your education, military, and transportation levels

void applyGrowth(float capacityDebuff)
{
    updateHousingLevel();

    if (housingAmount <= 0) return;
;
    float houMult = housingAmount * 0.1f;
    float eduMult = educationLevel * 0.025f;
    float milMult = militaryLevel * 0.010f;
    float transMult = transportationLevel * 0.015f;
    float techMult = technologyLevel * 0.050f;
    float totalMult = 1.0f + eduMult + milMult + transMult + techMult + houMult;

    int baseGrowth = (rand() % housingAmount) + 1;
    float randomFactor = static_cast<float>(rand()) / RAND_MAX * 1.0f;
    float capacityFactor = 1.0f - (float(populationAmount) / (housingAmount * 2));
    capacityFactor = max(0.0f, capacityFactor);

    int potentialGrowth = static_cast<int>(baseGrowth * totalMult * randomFactor * capacityFactor * capacityDebuff);

    if (populationAmount == 0 && housingAmount > 0)
        potentialGrowth = max(1, potentialGrowth + 1);

    populationAmount = min(populationAmount + max(potentialGrowth, 0), housingAmount * 2);

    if (capacityDebuff < 1.0f)
        capacityDebuff = min(1.0f, capacityDebuff + 0.1f);
}
