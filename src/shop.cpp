#include <iostream>
#include "globals.h"
#include "input.h"
#include "housing.h"
using namespace std;

void shop()
{
    string input;
    bool inShop = true;

    while (inShop)
    {
        cout << "\nSHOP MENU\n"
             << "Money: $" << moneyAmount << "\n"
             << "Options: housing (h) $100 | education (e) $200 | military (m) $500 | transportation (tr) $150 | technology (te) $300 | back (b)\n> ";
        cin >> input;

        if (input == "back" || input == "b")
        {
            cout << "Leaving shop...\n";
            inShop = false;
        }
        else if (input == "housing" || input == "h")
        {
            cout << "How many houses would you like to buy? (1 house = $100)\n> ";
            int num = getIntInput();
            int cost = 100 * num;

            if (moneyAmount < cost)
            {
                cout << "Not enough money!\n";
                continue;
            }
            else if ((housingAmount + num) > educationLevel * 2)
            {
                cout << "Your town isn't educated enough to manage more housing! (Try Upgrading Your Education)\n";
                continue;
            }
            else if ((housingAmount + num) > (transportationLevel * 3))
            {
                cout << "Your town doesn't have enough transportation for more housing! (Try Upgrading Your Transportation)\n";
                continue;
            }
            else if ((housingAmount + num) > technologyLevel * 5)
            {
                cout << "Your town doesn't have enough power to support more houses! (Try Upgrading Your Technology)\n";
                continue;
            }

            moneyAmount -= cost;
            housingAmount += num;
            updateHousingLevel();
            cout << "Bought " << num << " houses for $" << cost << "!\n";
        }
        else if (input == "education" || input == "e")
        {
            cout << "How many education levels would you like to buy? (1 level = $200)\n> ";
            int num = getIntInput();
            int cost = 200 * num;

            if (moneyAmount < cost)
            {
                cout << "Not enough money!\n";
                continue;
            }
            else if ((educationLevel + num) > housingAmount * 3)
            {
                cout << "Your town doesn't have enough housing for more schools! (Try Upgrading Your Housing)\n";
                continue;
            }
            else if ((educationLevel + num) > transportationLevel * 2.5)
            {
                cout << "Your transportation network can't support more schools! (Try Upgrading Your Tansporation)\n";
                continue;
            }
            else if ((educationLevel + num) > technologyLevel * 2)
            {
                cout << "Your town doesn't have enough technology to support more school! (Try Upgrading Your Technology)\n";
                continue;
            }

            moneyAmount -= cost;
            educationLevel += num;
            cout << "Education increased by " << num << "!\n";
        }
        else if (input == "military" || input == "m")
        {
            cout << "How many military levels would you like to buy? (1 level = $500)\n> ";
            int num = getIntInput();
            int cost = 500 * num;

            if (moneyAmount < cost)
            {
                cout << "Not enough money!\n";
                continue;
            }
            else if ((militaryLevel + num) > housingAmount * 5)
            {
                cout << "Your town doesn't have enough housing for more military units! (Try Upgrading Your Housing)\n";
                continue;
            }
            moneyAmount -= cost;
            militaryLevel += num;
            cout << "Military increased by " << num << "!\n";
        }
        else if (input == "transportation" || input == "tr")
        {
            cout << "How many transportation levels would you like to buy? (1 level = $150)\n> ";
            int num = getIntInput();
            int cost = 150 * num;

            if (moneyAmount < cost) {
                cout << "Not enough money!\n";
                continue;
            }

            moneyAmount -= cost;
            transportationLevel += num;
            cout << "Transportation increased by " << num << "!\n";
        }
        else if (input == "technology" || input == "te")
        {
            cout << "How many technology levels would you like to buy? (1 level = $300)\n> ";
            int num = getIntInput();
            int cost = 300 * num;

            if (moneyAmount < cost) {
                cout << "Not enough money!\n";
                continue;
            }
            else if ((technologyLevel + num) > educationLevel * 2)
            {
                cout << "Your town isn't educated enough to create technology this advanced! (Try Upgrading Your Education)\n";
                continue;
            }

            moneyAmount -= cost;
            technologyLevel += num;
            cout << "Technology increased by " << num << "!\n";
        }
        else
        {
            cout << "Invalid option!\n";
        }
    }
}
