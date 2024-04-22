#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>

#include <memory> // For smart pointers

// Forward declaration of BankAccount class
class BankAccount;

class Bank {
public:
    // Constructor and destructor
    Bank(const std::string& name);
    ~Bank();

    // Member function to add a new bank account
    void addAccount(const std::string& ownerName, double initialBalance);

    // Member function to add a new bank account
    void addAccount(const BankAccount& bankAccount);

    // Member function to perform a transfer between two accounts
    bool transfer(int fromAccountNumber, int toAccountNumber, double amount);

    // Member function to display all accounts and their balances
    void displayAllAccounts() const;

    // Member function to generate a report of all accounts
    void generateReport() const;

    const std::string& getBankName();

    BankAccount& getAccount(int accountNumber) ;

protected:
    std::string bankName;

private:
    std::vector<std::shared_ptr<BankAccount>> accounts;
    static int nextAccountNumber; // Static variable to generate unique account numbers

    // Private helper function to find an account by account number
    std::shared_ptr<BankAccount> findAccount(int accountNumber) const;

   
};

#endif // BANK_H