#include "bank.h"

 // For getting current time
class Bank;

int Bank::nextAccountNumber = 1000; // Initialize static member

// Constructor definition
Bank::Bank(const std::string& name) : bankName(name) {}

// Destructor definition
Bank::~Bank() {
    std::cout << "Bank " << bankName << " is closing\n";
    Utility::endl();
}

// Member function to add a new bank account
void Bank::addAccount(const std::string& ownerName, double initialBalance = 0) {
    int accountNumber = nextAccountNumber++;
    auto newAccount = std::make_shared<BankAccount>(ownerName, initialBalance, accountNumber);
    accounts.push_back(newAccount);
   // std::cout << "New account created for " << ownerName << " with account number " << accountNumber << "\n";
  //  std::cout << std::endl;
}

void Bank::addAccount(const BankAccount& bankAccount) {
    this->addAccount(bankAccount.getOwnerName(), bankAccount.getBalance());
}

const bool Bank::transfer(const BankAccount& srcBankAccount, const BankAccount& toBankAccount, double amount) {
    return transfer(srcBankAccount.getAccountId(), toBankAccount.getAccountId(), amount);
}

// Member function to perform a transfer between two accounts
const bool Bank::transfer(int fromAccountNumber, int toAccountNumber, double amount) {
    auto fromAccount = findAccount(fromAccountNumber);
    auto toAccount = findAccount(toAccountNumber);

    if (fromAccount && toAccount) {
        if (fromAccount->withdraw(amount)) {
            toAccount->deposit(amount);

            // Check if the transfer amount is above $1000
            if (amount >= 1000.0) {
                // Generate unique filename based on timestamp and account IDs
                std::time_t currentTime = std::time(nullptr);
                std::string timestamp = std::to_string(currentTime);
                std::string filename = "C:/Users/salva/source/repos/_cmake/main/resources/transfers/transfer_" + std::to_string(fromAccountNumber) + "_to_" + std::to_string(toAccountNumber) + "_" + timestamp + ".txt";

                // Open file for writing transfer details
                std::ofstream outFile(filename);
                if (outFile.is_open()) {
                    outFile << "Transfer Details\n";
                    outFile << "From Account (ID: " << fromAccountNumber << ") - Owner: " << fromAccount->getOwnerName() << "\n";
                    outFile << "To Account (ID: " << toAccountNumber << ") - Owner: " << toAccount->getOwnerName() << "\n";
                    outFile << "Amount Transferred: $" << std::fixed << std::setprecision(2) << amount << "\n";
                    outFile << "Transfer successful.\n";
                    outFile.close();
                    std::cout << "Transfer details written to file: " << filename << "\n";
                }
                else {
                    std::cerr << "Error: Unable to open file for writing transfer details.\n";
                }
            }
            else {
                // Amount is not above $1000, print transfer details to console only
                std::cout << "Transfer Details\n";
                std::cout << "From Account (ID: " << fromAccountNumber << ") - Owner: " << fromAccount->getOwnerName() << "\n";
                std::cout << "To Account (ID: " << toAccountNumber << ") - Owner: " << toAccount->getOwnerName() << "\n";
                std::cout << "Amount Transferred: $" << std::fixed << std::setprecision(2) << amount << "\n";
                std::cout << "Transfer successful.\n";
            }

            return true;
        }
        else {
            // Insufficient funds in the source account
            std::cerr << "Transfer failed. Insufficient funds in the source account.\n";
            return false;
        }
    }
    else {
        // Invalid account numbers
        std::cerr << "Invalid account numbers. Transfer aborted.\n";
        return false;
    }
}

// Member function to display all accounts and their balances
void Bank::displayAllAccounts() const {
    std::cout << "Bank Accounts for " << bankName << ":\n";
    for (const auto& account : accounts) {
        std::cout << "Account Number: " << account->getAccountId()
            << ", Owner: " << account->getOwnerName()
            << ", Balance: $" << std::fixed << std::setprecision(2) << account->getBalance() << "\n";
    }
    std::cout << std::endl;
}

// Member function to generate a report of all accounts
void Bank::generateReport() const {
    Utility::endl();
    std::cout << "Bank Report for " << bankName << ":\n";

    // Display total number of accounts and total balance in the bank
    std::cout << "Total Number of Accounts: " << accounts.size() << "\n";
    double totalBalance = 0.0;

    // Display detailed information for each account
    std::cout << "Account Information:\n";
    std::cout << "-------------------------------------\n";
    for (const auto& account : accounts) {

        std::cout << "Account Number: " << account->getAccountId() << "\n";
        std::cout << "Owner: " << account->getOwnerName() << "\n";
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << account->getBalance() << "\n";
        std::cout << "-------------------------------------\n";
        totalBalance += account->getBalance();
    }

    // Display total balance of all accounts in the bank
    std::cout << "Total Balance in Bank: $" << std::fixed << std::setprecision(2) << totalBalance << "\n";

    // Optional: Display additional information or breakdowns (e.g., by account type or balance range)

    Utility::endl();
}
const std::string& Bank::getBankName()  {

    return this->bankName;

}

BankAccount& Bank::getAccount(int accountNumber)  {
    for (const auto& account : accounts) {
        if (account->getAccountId() == accountNumber) {
            return *account;
        }
    }
    return *findAccount(accountNumber); // Account not found
}

// Private helper function to find an account by account number
std::shared_ptr<BankAccount> Bank::findAccount(int accountNumber) const {
    for (const auto& account : accounts) {
        if (account->getAccountId() == accountNumber) {
            return account;
        }
    }
    return nullptr; // Account not found
}