
#include "src/core/bank/bank_account.h"
#include "inventory.h"

namespace ExolorGame {
 

    class Character {

    private:
        std::string name;
        BankAccount* bank;
        Inventory* inventory;

    public:
        Character(std::string characterName, BankAccount* playerBank);

        Character(std::string characterName, int balance, int accountId);

        const std::string& getName();

        Inventory* getInventory();

        BankAccount* getBankAccount();

        void deposit(double amount);

        const bool withdraw(double amount);

        void displayBalance();
    };
}