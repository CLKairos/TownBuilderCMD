#ifndef LOAN_H
#define LOAN_H
#include <cstdint>
#include <iostream>
#include "globals.h"

void takeOutLoan();
void payLoan();
void viewLoanStatus();
void loanRepaymentLogic();

inline int64_t currentLoanAmount = 0;
inline int maxLoan = ((static_cast<int>(populationAmount)) * educationLevel);

#endif // LOAN_H