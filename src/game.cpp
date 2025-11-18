#include "globals.h"
#include "reputation.h"
#include "location.h"
#include "shop.h"
#include "save.h"
#include "input.h"
#include "growth.h"
#include "randomEvents.h"
#include "game.h"
#include <cstdlib>
#include <iostream>
using namespace std;

//game loop logic

void gameLoop()
{
    bool running = false;
    string input;
    float capacityDebuff = 1.0f;
    int disasterCooldown = 0;

    if (setLocation == ""){
        selectLocation();
    } else {
        running = true;
    }

    while (running)
    {
        applyGrowth(capacityDebuff);
        calcReputation();
        moneyAmount += (rand() % populationAmount * 2) + 1;

        system("PAUSE"); 
        system("cls"); 

        cout << "\nTownBuilderCMD\n"
             << "Money: $" << moneyAmount << "\n"
             << "Population: " << populationAmount << "\n"
             << "Houses: " << housingAmount << " (Level " << housingLevel << ")\n"
             << "Education: " << educationLevel << "\n"
             << "Military: " << militaryLevel << "\n"
             << "Transportation: " << transportationLevel << "\n"
             << "Technology: " << technologyLevel << "\n"
             << "Options: shop (sh), wait (w), save (sa), exit (e)\n> ";

        cin >> input;

        if (input == "exit" || input == "e")
        {
            saveGame();
            running = false;
        }
        else if (input == "save" || input == "sa")
        {
            saveGame();
        }
        else if (input == "shop" || input == "sh")
        {
            shop();
        }
        else if (input == "wait" || input == "w")
        {
            cout << "How many turns would you like to wait? (max 10)\n> ";
            int turns = getIntInput();
            turns = min(turns, 10);

            for (int i = 0; i < turns; i++)
            {
                cout << "Time passes...\n";
                if (disasterCooldown > 0) disasterCooldown--;
                handleRandomEvents(disasterCooldown, capacityDebuff);
                applyGrowth(capacityDebuff);
                moneyAmount += populationAmount * 2;
            }
        }
        else
        {
            cout << "Invalid option!\n";
        }
    }
}
