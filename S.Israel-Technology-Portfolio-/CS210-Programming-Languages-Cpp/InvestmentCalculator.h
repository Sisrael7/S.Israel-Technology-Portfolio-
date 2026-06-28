
// File: InvestmentCalculator.h
// Description: Header file for the InvestmentCalculator class

#ifndef INVESTMENTCALCULATOR_H
#define INVESTMENTCALCULATOR_H

class InvestmentCalculator {
private:
    double initialInvestment;
    double monthlyDeposit;
    double annualInterestRate;
    int numYears;

public:
    // Constructor
    InvestmentCalculator(double initInv, double monDep, double intRate, int years);

    // Function to display balances without monthly deposits
    void displayWithoutMonthlyDeposit();

    // Function to display balances with monthly deposits
    void displayWithMonthlyDeposit();
};

#endif
