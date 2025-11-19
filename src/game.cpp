#include <cstdlib>
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include "globals.h"
#include "game.h"
#include "reputation.h"
#include "location.h"
#include "shop.h"
#include "save.h"
#include "input.h"
#include "growth.h"
#include "randomEvents.h"
#include "loan.h"

// Forward declaration
void clearInputBuffer();

// Helper function to clear input buffer
void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void gameLoop()
{
    bool running = false;
    std::string input;
    int disasterCooldown = 0;
    float capacityDebuff = 1.0f; // Initialize as float to match function signature

    if (setLocation == ""){
        selectLocation();
    } else {
        running = true;
    }

    while (running)
    {
        applyGrowth(capacityDebuff);
        calcReputation();
        maxLoan = ((static_cast<int>(populationAmount)) * educationLevel);
        
        if (maxLoan <= 100)
        {
            std::cout << "\nTownBuilderCMD\n"
             << "Money: $" << moneyAmount << "\n"
             << "Population: " << populationAmount << "\n"
             << "Houses: " << housingAmount << " (Level " << housingLevel << ")\n"
             << "Education: " << educationLevel << "\n"
             << "Military: " << militaryLevel << "\n"
             << "Transportation: " << transportationLevel << "\n"
             << "Technology: " << technologyLevel << "\n"
             << "Reputation: " << reputationLevel << "\n"
             << "Location: "<< setLocation << "\n\n"
             << "Options: shop (sh), wait (w), save (sa), exit (e)\n> ";
        } else {
            std::cout << "\nTownBuilderCMD\n"
             << "Money: $" << moneyAmount << "\n"
             << "Population: " << populationAmount << "\n"
             << "Houses: " << housingAmount << " (Level " << housingLevel << ")\n"
             << "Education: " << educationLevel << "\n"
             << "Military: " << militaryLevel << "\n"
             << "Transportation: " << transportationLevel << "\n"
             << "Technology: " << technologyLevel << "\n"
             << "Reputation: " << reputationLevel << "\n"
             << "Location: "<< setLocation << "\n\n"
             << "Options: shop (sh), take loan (tl), check loan (cl), pay loan (pl), wait (w), save (sa), exit (e)\n> ";
        }

        if (!(std::cin >> input))
        {
            clearInputBuffer();
            std::cout << "Invalid input! Please try again.\n";
            continue;
        }

        // Convert input to lowercase for case-insensitive comparison
        for (char &c : input) {
            c = std::tolower(static_cast<unsigned char>(c));
        }

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
        else if (input == "take loan" || input == "tl")
        {
            takeOutLoan();
        }
        else if (input == "check loan" || input == "cl")
        {
            viewLoanStatus();
        }
        else if (input == "pay loan" || input == "pl")
        {
            payLoan();
        }
        else if (input == "wait" || input == "w")
        {
            std::cout << "How many turns would you like to wait? (max 10)\n> ";
            int turns = getIntInput();
            
            if (turns <= 0) {
                std::cout << "Invalid number of turns!\n";
                continue;
            }
            
            turns = std::min(turns, 10);

            for (int i = 0; i < turns; i++)
            {
                std::cout << "Time passes... (Turn " << (i + 1) << "/" << turns << ")\n";
                if (disasterCooldown > 0) disasterCooldown--;
                handleRandomEvents(disasterCooldown, capacityDebuff);
                applyGrowth(capacityDebuff);
                calcReputation();
                loanRepaymentLogic();
                moneyAmount += populationAmount * 2;
            }
            
            std::cout << "\nWaiting complete! " << turns << " turn(s) have passed.\n";
        }
        else
        {
            std::cout << "Invalid option! Please choose from the available commands.\n";
        }
        
        // Clear any remaining input
        clearInputBuffer();
    }
}