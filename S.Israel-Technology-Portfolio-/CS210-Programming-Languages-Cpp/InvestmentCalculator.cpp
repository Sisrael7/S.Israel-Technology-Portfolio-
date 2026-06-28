//  StephenIsrael
// Date: 10/5/2025
// File: InvestmentCalculator.cpp
// Description: Implementation of the InvestmentCalculator class

#include <iostream>
#include <iomanip>
#include "InvestmentCalculator.h"
using namespace std;

// Constructor definition
InvestmentCalculator::InvestmentCalculator(double initInv, double monDep, double intRate, int years) {
    initialInvestment = initInv;
    monthlyDeposit = monDep;
    annualInterestRate = intRate;
    numYears = years;
}

// Function to display report without monthly deposits
void InvestmentCalculator::displayWithoutMonthlyDeposit() {
    double balance = initialInvestment;
    double yearlyInterest;

    cout << endl;
    cout << "  Balance and Interest Without Additional Monthly Deposits" << endl;
    cout << "==============================================================" << endl;
    cout << "Year" << setw(20) << "Year End Balance" << setw(30) << "Year End Earned Interest" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int year = 1; year <= numYears; year++) {
        yearlyInterest = 0;

        for (int month = 1; month <= 12; month++) {
            double monthlyInterest = balance * ((annualInterestRate / 100) / 12);
            balance += monthlyInterest;
            yearlyInterest += monthlyInterest;
        }

        cout << fixed << setprecision(2);
        cout << year << setw(20) << balance << setw(30) << yearlyInterest << endl;
    }
}

// Function to display report with monthly deposits
void InvestmentCalculator::displayWithMonthlyDeposit() {
    double balance = initialInvestment;
    double yearlyInterest;

    cout << endl;
    cout << "  Balance and Interest With Additional Monthly Deposits" << endl;
    cout << "==============================================================" << endl;
    cout << "Year" << setw(20) << "Year End Balance" << setw(30) << "Year End Earned Interest" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int year = 1; year <= numYears; year++) {
        yearlyInterest = 0;

        for (int month = 1; month <= 12; month++) {
            balance += monthlyDeposit;
            double monthlyInterest = balance * ((annualInterestRate / 100) / 12);
            balance += monthlyInterest;
            yearlyInterest += monthlyInterest;
        }

        cout << fixed << setprecision(2);
        cout << year << setw(20) << balance << setw(30) << yearlyInterest << endl;
    }
}
// Name: Stephen Israel
// Course: CS-210
// Date: [Insert Date]
// File: InvestmentCalculator.cpp
// Description: Implementation of the InvestmentCalculator class

#include <iostream>
#include <iomanip>
#include "InvestmentCalculator.h"
using namespace std;

// Constructor definition
InvestmentCalculator::InvestmentCalculator(double initInv, double monDep, double intRate, int years) {
    initialInvestment = initInv;
    monthlyDeposit = monDep;
    annualInterestRate = intRate;
    numYears = years;
}

// Function to display report without monthly deposits
void InvestmentCalculator::displayWithoutMonthlyDeposit() {
    double balance = initialInvestment;
    double yearlyInterest;

    cout << endl;
    cout << "  Balance and Interest Without Additional Monthly Deposits" << endl;
    cout << "==============================================================" << endl;
    cout << "Year" << setw(20) << "Year End Balance" << setw(30) << "Year End Earned Interest" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int year = 1; year <= numYears; year++) {
        yearlyInterest = 0;

        for (int month = 1; month <= 12; month++) {
            double monthlyInterest = balance * ((annualInterestRate / 100) / 12);
            balance += monthlyInterest;
            yearlyInterest += monthlyInterest;
        }

        cout << fixed << setprecision(2);
        cout << year << setw(20) << balance << setw(30) << yearlyInterest << endl;
    }
}

// Function to display report with monthly deposits
void InvestmentCalculator::displayWithMonthlyDeposit() {
    double balance = initialInvestment;
    double yearlyInterest;

    cout << endl;
    cout << "  Balance and Interest With Additional Monthly Deposits" << endl;
    cout << "==============================================================" << endl;
    cout << "Year" << setw(20) << "Year End Balance" << setw(30) << "Year End Earned Interest" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int year = 1; year <= numYears; year++) {
        yearlyInterest = 0;

        for (int month = 1; month <= 12; month++) {
            balance += monthlyDeposit;
            double monthlyInterest = balance * ((annualInterestRate / 100) / 12);
            balance += monthlyInterest;
            yearlyInterest += monthlyInterest;
        }

        cout << fixed << setprecision(2);
        cout << year << setw(20) << balance << setw(30) << yearlyInterest << endl;
    }
}
