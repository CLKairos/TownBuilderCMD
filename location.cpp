#include "location.h"
#include "game.h"
#include "randomEvents.h"
#include <iostream>

void selectLocation() {
    int inpt;
    std::cout << "Please select a location!\n 1. United States\n 2. Russia\n 3. United Kingdom\n 4. Finland\n 5. Mexico\n";
    std::cin >> inpt;
    while (true) {
        if (inpt == 1) {
            std::cout << "You have chosen the location UNITED STATES!\n";
            setLocation = "United States";
            gameLoop();
            break;
        }
        if (inpt == 2) {
            std::cout << "You have chosen the location RUSSIA!\n";
            setLocation = "Russia";
            gameLoop();
            break;
        }
        if (inpt == 3) {
            std::cout << "You have chosen the location UNITED KINGDOM!\n";
            setLocation = "United Kingdom";
            gameLoop();
            break;
        }
        if (inpt == 4) {
            std::cout << "You have chosen the location FINLAND";
            setLocation = "Finland";
            gameLoop();
            break;
        }
        if (inpt == 5) {
            std::cout << "You have chosen the location MEXICO";
            setLocation = "Mexico";
            gameLoop();
            break;
        }
        else {
            std::cout << "Invalid Answer Choice!\n";
        }
    }
}