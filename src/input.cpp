#include <iostream>
#include <limits>
#include "globals.h"
#include "input.h"

using namespace std;

int getIntInput()
{
    int num;
    while (true)
    {
        if (cin >> num) // valid integer
            return num;

        // Invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
}
