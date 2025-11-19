#include <cstdlib>
#include <algorithm>
#include "globals.h"
#include "growth.h"
#include "housing.h"

using namespace std;

// Population growth logic, based on your education, military, and transportation levels

void applyGrowth(float capacityDebuff)
{
    updateHousingLevel();

    if (housingAmount <= 0) return;

    // Calculate multipliers from various systems
    float houMult = housingAmount * 0.1f;
    float eduMult = educationLevel * 0.025f;
    float milMult = militaryLevel * 0.010f;
    float transMult = transportationLevel * 0.015f;
    float techMult = technologyLevel * 0.050f;
    float totalMult = 1.0f + eduMult + milMult + transMult + techMult + houMult;

    // Calculate base growth with proper random factor
    int baseGrowth = (rand() % housingAmount) + 1;
    float randomFactor = float(rand()) / RAND_MAX;  // Fixed: proper float division
    
    // Calculate capacity factor (slows growth as population approaches capacity)
    float potentialCapacityFactor = 1.0f - (float(populationAmount) / (housingAmount * 2));
    capacityFactor = max(0.0f, potentialCapacityFactor);

    // Calculate final growth amount
    int potentialGrowth = static_cast<int>(baseGrowth * totalMult * randomFactor * capacityFactor * capacityDebuff);

    // Ensure at least 1 person spawns if housing exists but population is 0
    if (populationAmount == 0 && housingAmount > 0)
        potentialGrowth = max(1, potentialGrowth);

    // Apply growth with cap at 2x housing capacity
    populationAmount = min(populationAmount + max(potentialGrowth, 0), housingAmount * 2);

    // Gradually restore capacity debuff
    if (capacityDebuff < 1.0f)
        capacityDebuff = min(1.0f, capacityDebuff + 0.1f);
}