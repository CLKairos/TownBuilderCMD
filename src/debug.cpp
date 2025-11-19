#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "globals.h"
#include "loan.h"
#include "growth.h"

class DebugCommandHandler {
private:
    std::map<std::string, std::function<void(const std::string&)>> commands;

public:
    DebugCommandHandler() {
        registerCommand("help", [this](const std::string&) { showHelp(); });
        registerCommand("status", [this](const std::string&) { showStatus(); });
        registerCommand("clear", [this](const std::string&) { clearScreen(); });
        registerCommand("variables", [this](const std::string&) {
            std::cout << "Money: " << moneyAmount << "\n"
                      << "Population: " << populationAmount << "\n"
                      << "Reputation: " << reputationLevel << "\n"
                      << "Housing Level: " << housingLevel << "\n"
                      << "Housing Amount: " << housingAmount << "\n"
                      << "Military Level: " << militaryLevel << "\n"
                      << "Education Level: " << educationLevel << "\n"
                      << "Transportation Level: " << transportationLevel << "\n"
                      << "Technology Level: " << technologyLevel << "\n"
                      << "Current Loan Amount: " << currentLoanAmount << "\n"
                      << "Days to Repay Loan: " << daysToRepayLoan << "\n"
                      << "Location: " << setLocation << "\n"
                      << "Max Loan: " << maxLoan << "\n"
                      << "Potential Growth: " << capacityFactor << "\n";
        });
    }

    void registerCommand(const std::string& name, std::function<void(const std::string&)> handler) {
        commands[name] = handler;
    }

    void execute(const std::string& input) {
        size_t spacePos = input.find(' ');
        std::string cmd = input.substr(0, spacePos);
        std::string args = (spacePos != std::string::npos) ? input.substr(spacePos + 1) : "";

        auto it = commands.find(cmd);
        if (it != commands.end()) {
            it->second(args);
        } else {
            std::cout << "Unknown command: " << cmd << std::endl;
        }
    }

private:
    void showHelp() {
        std::cout << "Available commands:\n"
                  << "  help   - Show this message\n"
                  << "  status - Show game status\n"
                  << "  clear  - Clear console\n";
    }

    void showStatus() {
        std::cout << "Game status: Running\n";
    }

    void clearScreen() {
        system("cls");
    }
};