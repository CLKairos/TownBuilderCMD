#include "save.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "globals.h"
#include "housing.h"
#include "location.h"

using namespace std;

void saveGame()
{
    ofstream saveFile("save.txt");
    if (!saveFile)
    {
        cerr << "Error saving game!\n";
        return;
    }

    saveFile << moneyAmount << ","
             << populationAmount << ","
             << reputationLevel << ","
             << housingLevel << ","
             << housingAmount << ","
             << militaryLevel << ","
             << educationLevel << ","
             << transportationLevel << ","
             << technologyLevel << ","
             << setLocation;

    saveFile.close();
    cout << "Game saved successfully!\n";
}

void loadGame()
{
    ifstream saveFile("save.txt");
    if (!saveFile)
    {
        cout << "No save file found. Starting new game...\n";
        moneyAmount = 1000;
        populationAmount = 0;
        reputationLevel = 0;
        housingLevel = 1;
        housingAmount = 1;
        militaryLevel = 0;
        educationLevel = 0;
        transportationLevel = 3;
        technologyLevel = 1;
        setLocation = "";
        return;
    }

    string line;
    getline(saveFile, line);
    saveFile.close();

    stringstream ss(line);
    string temp;

    try {
        getline(ss, temp, ','); moneyAmount = stoi(temp);
        getline(ss, temp, ','); populationAmount = stoi(temp);
        getline(ss, temp, ','); reputationLevel = stoi(temp);
        getline(ss, temp, ','); housingLevel = stoi(temp);
        getline(ss, temp, ','); housingAmount = stoi(temp);
        getline(ss, temp, ','); militaryLevel = stoi(temp);
        getline(ss, temp, ','); educationLevel = stoi(temp);
        getline(ss, temp, ','); transportationLevel = stoi(temp);
        getline(ss, temp, ','); technologyLevel = stoi(temp);
        getline(ss, temp, ','); setLocation = temp;

        cout << "Loaded save data successfully.\n";
    } catch (...)
    {
        cout << "Save file corrupted. Starting new game.\n";
        moneyAmount = 1000;
        populationAmount = 0;
        reputationLevel = 0;
        housingLevel = 1;
        housingAmount = 1;
        militaryLevel = 0;
        educationLevel = 0;
        transportationLevel = 3;
        technologyLevel = 1;
        setLocation = "";
    }

    updateHousingLevel();
}
