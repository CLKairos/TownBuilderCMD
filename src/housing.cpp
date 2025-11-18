#include "globals.h"
#include "housing.h"

//updates housing LEVEL based on increments.
void updateHousingLevel()
{
    if (housingAmount > 1000000) housingLevel = 8;
    else if (housingAmount > 100000) housingLevel = 7;
    else if (housingAmount > 10000) housingLevel = 6;
    else if (housingAmount > 1000) housingLevel = 5;
    else if (housingAmount > 500) housingLevel = 4;
    else if (housingAmount > 100) housingLevel = 3;
    else if (housingAmount > 50) housingLevel = 2;
    else if (housingAmount > 10) housingLevel = 1;
    else housingLevel = 0;
}
