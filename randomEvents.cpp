#include <iostream>
#include <algorithm>
#include "globals.h"
#include "randomEvents.h"
#include "location.h"

using namespace std;

void handleRandomEvents(int &eventCooldown, float &capacityDebuff)
{
    if (eventCooldown > 0) return;

    float warRoll = 5;
    int roll = rand() % 500 + 1;

    if (setLocation == "United States") {
        warRoll *= 2;
    }
    else if (setLocation == "Russia") {
        warRoll *= 4;
    }
    else if (setLocation == "United Kingdom") {
        warRoll *= 1;
    }
    else if (setLocation == "Finland") {
        warRoll *= .75;
    }
    else if (setLocation == "Mexico") {
        warRoll *= 1.5;
    }

    // Deadly disease
    if (roll == 1 && populationAmount > 50)
    {
        cout << "A deadly disease killed half your population!\n";
        populationAmount = max(1LL, static_cast<long long>(populationAmount) / 2);
        capacityDebuff = 0.25f;
        eventCooldown = 25;
    }

    // Rival town war
    else if (roll <= warRoll && populationAmount >= 50)
    {
        float militaryEffectiveness = 1.0f;
        cout << "A rivaling town started a war!\n";
        int safeMil = max(militaryLevel, 1);
        float rivalPower = static_cast<float>(rand() % (safeMil * 2) + 1);

        if (educationLevel * 2 < militaryLevel) {
            militaryEffectiveness *= 0.75f;
            cout << "Your military isn't as smart as they should be... (Try Upgrading Your Education)\n";
        }
        if (technologyLevel < militaryLevel) {
            militaryEffectiveness *= 0.85f;
            cout << "Your military isn't as advanced as they should be... (Try Upgrading Your Technology)\n";
        }
        if (transportationLevel < militaryLevel) {
            militaryEffectiveness *= 0.70f;
            cout << "Your military can't go anywhere... (Try Upgrading Your Transportation)\n";
        }

        // compute a sensible actual military power from available stats (safeMil is at least 1)
        float actualMilitaryPower = static_cast<float>(safeMil) * 10.0f
                                    + static_cast<float>(technologyLevel) * 2.0f
                                    + static_cast<float>(educationLevel) * 1.5f
                                    + static_cast<float>(transportationLevel) * 1.0f;

        float effectiveMilitaryPower = actualMilitaryPower * militaryEffectiveness;

        if (rivalPower > effectiveMilitaryPower)
        {
            cout << "You lost the war! Half your assets were destroyed.\n";
            populationAmount = max(1LL, static_cast<long long>(populationAmount) / 2);
            transportationLevel = max(1LL, static_cast<long long>(transportationLevel) / 2);
            educationLevel = max(1LL, static_cast<long long>(educationLevel) / 2);
            militaryLevel = max(1LL, static_cast<long long>(militaryLevel) / 2);
            housingAmount = max(1LL, static_cast<long long>(housingAmount) / 2);
            moneyAmount = max(0LL, static_cast<long long>(moneyAmount) / 2);
        }
        else
        {
            cout << "You won the war! 30% increase across all stats.\n";
            populationAmount = static_cast<int>(populationAmount * 1.3f);
            transportationLevel = static_cast<int>(transportationLevel * 1.3f);
            educationLevel = static_cast<int>(educationLevel * 1.3f);
            militaryLevel = static_cast<int>(militaryLevel * 1.3f);
            housingAmount = static_cast<int>(housingAmount * 1.3f);
            moneyAmount = static_cast<int>(moneyAmount * 1.3f);
        }
        eventCooldown = 15;
    }
    else if (roll <= 7 && housingAmount > 5)
    {
        cout << "A fire destroyed half your houses!\n";
        housingAmount = max(1LL, static_cast<long long>(housingAmount) / 2);
        eventCooldown = 10;
    }
    // Sinkhole
    else if (roll == 8 && housingAmount > 40) {
        cout << "A sink hole swallowed half of your town\n and you lost half of your housing and transportation.\n";
        housingAmount = max(1LL, static_cast<long long>(housingAmount) / 2);
        transportationLevel = max(1LL, static_cast<long long>(transportationLevel) / 2);
        eventCooldown = 15;
    }
    // Fossil discovery
    else if (roll <= 14) {
        int fossilWorth = (rand() % 1200) + 120;
        cout << "Your town discovered a fossil! You gained $" << fossilWorth << "!\n";
        moneyAmount += fossilWorth;
        eventCooldown = (rand() % 6) + 7;
    }
    // Oil discovery
    else if (roll <= 20) {
        int oilWorth = (rand() % 5000) + 150;
        cout << "Your town discovered oil! You gained $" << oilWorth << "!\n";
        moneyAmount += oilWorth;
        eventCooldown = 19;
    }
    // New invention
    else if (roll <= 27) {
        int inventionWorth = (rand() % 23500) + 150;
        cout << "Your town discovered a new invention! You gained $" << inventionWorth << ", as well as an increased technology level and education level!\n";
        moneyAmount += inventionWorth;
        technologyLevel += 4;
        educationLevel += 7;
        eventCooldown = 20;
    }
    // Baby boom
    else if (roll <= 32 && housingAmount > 10) {
        int newCitizens = (rand() % (populationAmount / 4)) + 5;
        cout << "A baby boom occurred! You gained " << newCitizens << " new citizens!\n";
        populationAmount += newCitizens;
        eventCooldown = 12;
    }
    // Natural disaster - Earthquake
    else if (roll <= 35 && (housingAmount > 20 || transportationLevel > 5)) {
        cout << "An earthquake shook your town! You lost 30% of housing and transportation!\n";
        housingAmount = max(1, static_cast<int>(housingAmount * 0.7f));
        transportationLevel = max(1, static_cast<int>(transportationLevel * 0.7f));
        eventCooldown = 18;
    }
    // Trade caravan
    else if (roll <= 40 && transportationLevel > 3) {
        int tradeProfit = (rand() % 2000) + 300;
        cout << "A trade caravan passed through your town! You gained $" << tradeProfit << "!\n";
        moneyAmount += tradeProfit;
        eventCooldown = 8;
    }
    // Scholar migration
    else if (roll <= 44 && educationLevel > 5) {
        cout << "Scholars from afar heard about your town! Education level increased by 3!\n";
        educationLevel += 3;
        populationAmount += (rand() % 8) + 3;
        eventCooldown = 15;
    }
    // Flood
    else if (roll <= 47 && populationAmount > 30) {
        cout << "A flood devastated your town! You lost 25% of population and housing!\n";
        populationAmount = max(1, static_cast<int>(populationAmount * 0.75f));
        housingAmount = max(1, static_cast<int>(housingAmount * 0.75f));
        eventCooldown = 14;
    }
    // Tourism boom
    else if (roll <= 51 && (educationLevel > 8 || technologyLevel > 6)) {
        int touristMoney = (rand() % 4000) + 500;
        cout << "Tourists are flocking to your advanced town! You gained $" << touristMoney << "!\n";
        moneyAmount += touristMoney;
        eventCooldown = 10;
    }
    // Technological breakthrough
    else if (roll <= 54 && technologyLevel > 10) {
        cout << "Your scientists made a breakthrough! Technology level +5 and gained $1500!\n";
        technologyLevel += 5;
        moneyAmount += 1500;
        eventCooldown = 16;
    }
    // Bandit raid
    else if (roll <= 57 && militaryLevel < 5 && moneyAmount > 100) {
        long long stolen = min(static_cast<long long>(moneyAmount) / 3, (long long)((rand() % 800) + 200));
        cout << "Bandits raided your poorly defended town! You lost $" << stolen << "!\n";
        moneyAmount = max(0LL, static_cast<long long>(moneyAmount) - stolen);
        eventCooldown = 9;
    }
    // Festival
    else if (roll <= 61 && populationAmount > 25) {
        int festivalCost = (rand() % 300) + 100;
        int populationGain = (rand() % 15) + 5;
        cout << "Your town held a grand festival! Cost $" << festivalCost << " but attracted " << populationGain << " new residents!\n";
        moneyAmount = max(0LL, static_cast<long long>(moneyAmount) - festivalCost);
        populationAmount += populationGain;
        eventCooldown = 11;
    }
    // Meteor strike
    else if (roll == 62) {
        int meteorDamage = (rand() % 20) + 10;
        int meteorValue = (rand() % 3000) + 500;
        cout << "A meteor struck your town! Lost " << meteorDamage << " population, but rare materials worth $" << meteorValue << " were found!\n";
        populationAmount = max(1LL, static_cast<long long>(populationAmount) - meteorDamage);
        moneyAmount += meteorValue;
        eventCooldown = 20;
    }
    // Infrastructure collapse
    else if (roll <= 64 && transportationLevel > 10) {
        cout << "Poor maintenance caused infrastructure to collapse! Transportation level cut by 40%!\n";
        transportationLevel = max(1, static_cast<int>(transportationLevel * 0.6f));
        eventCooldown = 13;
    }
    // 67 Easter egg
    else if (roll == 67) {
        cout << "67! You gained $67!\n";
        moneyAmount += 67;
        eventCooldown = 41;
    }
    // Gold rush
    else if (roll == 70 && populationAmount < 200) {
        int goldRushPop = (rand() % 40) + 20;
        int goldRushMoney = (rand() % 6000) + 2000;
        cout << "Gold rush! " << goldRushPop << " miners arrived and you gained $" << goldRushMoney << "!\n";
        populationAmount += goldRushPop;
        moneyAmount += goldRushMoney;
        eventCooldown = 17;
    }
    // Plague of locusts
    else if (roll <= 72 && populationAmount > 40) {
        int locustCost = (rand() % 1500) + 500;
        cout << "A plague of locusts destroyed crops! You lost $" << locustCost << "!\n";
        moneyAmount = max(0LL, static_cast<long long>(moneyAmount) - locustCost);
        eventCooldown = 11;
    }
    // University founded
    else if (roll <= 74 && educationLevel > 15 && moneyAmount > 2000) {
        cout << "A prestigious university was founded in your town! Education +8, but cost $2000!\n";
        educationLevel += 8;
        moneyAmount = max(0LL, static_cast<long long>(moneyAmount) - 2000);
        populationAmount += (rand() % 20) + 10;
        eventCooldown = 22;
    }
    // Industrial revolution
    else if (roll == 75 && technologyLevel > 20) {
        cout << "Industrial revolution! All stats increased by 20%!\n";
        populationAmount = static_cast<int>(populationAmount * 1.2f);
        transportationLevel = static_cast<int>(transportationLevel * 1.2f);
        educationLevel = static_cast<int>(educationLevel * 1.2f);
        technologyLevel = static_cast<int>(technologyLevel * 1.2f);
        housingAmount = static_cast<int>(housingAmount * 1.2f);
        moneyAmount = static_cast<int>(moneyAmount * 1.2f);
        eventCooldown = 25;
    }
    // Refugee crisis
    else if (roll <= 78) {
        int refugees = (rand() % 30) + 15;
        int housingNeeded = refugees / 3;
        if (housingAmount >= housingNeeded) {
            cout << refugees << " refugees arrived and integrated successfully! Population increased!\n";
            populationAmount += refugees;
        } else {
            cout << refugees << " refugees arrived but you lack housing! They moved on...\n";
        }
        eventCooldown = 10;
    }
    // Ancient ruins discovered
    else if (roll <= 80) {
        int ruinsValue = (rand() % 5000) + 1000;
        cout << "Ancient ruins were discovered! Gained $" << ruinsValue << " and Education +2!\n";
        moneyAmount += ruinsValue;
        educationLevel += 2;
        eventCooldown = 14;
    }
    // Corruption scandal
    else if (roll <= 82 && moneyAmount > 1000) {
        int embezzled = (rand() % (moneyAmount / 5)) + 200;
        cout << "A corruption scandal was exposed! Lost $" << embezzled << " and 10 citizens!\n";
        moneyAmount = max(0LL, static_cast<long long>(moneyAmount) - embezzled);
        populationAmount = max(1LL, static_cast<long long>(populationAmount) - 10);
        eventCooldown = 12;
    }
    // Peaceful alliance
    else if (roll <= 84 && militaryLevel > 8) {
        int allianceBonus = (rand() % 2500) + 800;
        cout << "You formed a peaceful alliance with a neighboring town! Gained $" << allianceBonus << "!\n";
        moneyAmount += allianceBonus;
        militaryLevel += 2;
        eventCooldown = 15;
    }
}