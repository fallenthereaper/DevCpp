#include "bank_account.h"
#include <iostream>
#include <iomanip>


// Constructor definition
BankAccount::BankAccount(const std::string& ownerName, double initialBalance, int accountId)
    : ownerName(ownerName), balance(initialBalance), accountId(accountId) {}

// Member function to deposit money into the account
BankAccount BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        // Add deposit transaction to history
        transactionHistory.push_back([=]() {
            std::cout << "Deposited $" << amount << "\n";
            });
    }
    else {
        transactionHistory.push_back([=]() {
            std::cerr << "Invalid deposit amount. Amount must be positive.\n";
            });
    }
    return *this;
}

// Member function to withdraw money from the account
bool BankAccount::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        // Add withdrawal transaction to history
        transactionHistory.push_back([=]() {
            std::cout << "Withdrawn $" << amount << "\n";
            });
        return true;
    }
    else {
        transactionHistory.push_back([=]() {
            std::cerr << "Failed to withdraw $" << amount << ". Insufficient funds or invalid amount.\n";
            });
        return false;
    }
}

// Member function to apply interest to the account balance
void BankAccount::applyInterest(double rate) {
    double interest = balance * rate / 100;
    deposit(interest); // Apply interest by depositing into the account
}

// Member function to get the current balance of the account
double BankAccount::getBalance() const {
    return balance;
}

// Member function to get the owner's name of the account
std::string BankAccount::getOwnerName() const {
    return ownerName;
}

// Member function to get the accountId of the account
int BankAccount::getAccountId() const {
    return accountId;
}

// Member function to display transaction history
void BankAccount::displayTransactionHistory() const {
    std::cout << "Transaction History for Account ID: " << accountId << " (Owner: " << ownerName << "):\n";
    for (const auto& transaction : transactionHistory) {
        transaction(); // Invoke each lambda in the transaction history
    }
    std::cout << std::endl;
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";

    std::cout << std::endl;

}