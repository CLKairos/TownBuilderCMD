#include "globals.h"
#include "loan.h"
#include <iostream>

void takeOutLoan(){
    if (currentLoanAmount > 0){
        std::cout << "You must pay off your current loan before taking out another!\n";
        return;
    }
    maxLoan = ((static_cast<int>(populationAmount)) * educationLevel);
    std::cout << "How much would you like to take out? Max Loan Amount: " << maxLoan << "\n";
    std::cin >> currentLoanAmount;
    if (currentLoanAmount > maxLoan){
        std::cout << "You cannot take out that much!\n";
        return;
    }
    daysToRepayLoan = 30;
    moneyAmount += currentLoanAmount;
    std::cout << "You have taken out a loan of $" << currentLoanAmount << ". You have 30 days to repay it.\n";
}

void payLoan(){
    if (currentLoanAmount <= 0){
        std::cout << "You have no loan to pay off!\n";
        return;
    }
    viewLoanStatus();
    std::cout << "How much would you like to pay off?\n";
    __int64 payAmount;
    std::cin >> payAmount;
    if (payAmount > static_cast<int>(moneyAmount)){
        std::cout << "You do not have enough money!\n";
        return;
    }
    moneyAmount -= payAmount;
    currentLoanAmount -= payAmount;
}

void viewLoanStatus(){
    std::cout << "You currently owe $" << currentLoanAmount <<" in loans. Which is due in " << daysToRepayLoan << " Days \n"; // Placeholder for actual loan tracking
}

void loanRepaymentLogic(){
    if (currentLoanAmount <= 0){ 
        return;
    }
    else {
        daysToRepayLoan--;
    }

    if (daysToRepayLoan <= 0){
        std::cout << "You have failed to repay your loan on time! The loan sharks took their money back and then some...\n";
        int64_t penalty = static_cast<int64_t>(currentLoanAmount * 1.50);
        moneyAmount -= penalty;
        currentLoanAmount = 0;
    }
}