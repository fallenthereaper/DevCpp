#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <vector>
#include <functional>
#include "src/core/utils/functional.h"
#include "src/core/utils/utility.h"

class BankAccount {
public:
    // Constructor to initialize the bank account with owner's name, initial balance, and accountId
    BankAccount(const std::string& ownerName, double initialBalance, int accountId);

    // Member function to deposit a specified amount into the account
    BankAccount deposit(const double amount);

    // Member function to withdraw a specified amount from the account
    // Returns true if withdrawal is successful, false otherwise (insufficient funds)
    const bool withdraw(double amount);

    // Member function to apply interest to the account balance
    void applyInterest(double rate);

    // Member function to get the current balance of the account
    double getBalance() const;

    // Member function to get the owner's name of the account
    std::string getOwnerName() const;

    // Member function to get the accountId of the account
    int getAccountId() const;

    // Member function to display transaction history
    void displayTransactionHistory() const;

private:
    std::string ownerName;                 // Owner's name of the bank account
    double balance;                        // Current balance in the bank account
    int accountId;                         // Unique identifier for the bank account
    std::vector<std::function<void()>> transactionHistory;  // Transaction history (using lambdas)
};

#endif // BANK_ACCOUNT_H