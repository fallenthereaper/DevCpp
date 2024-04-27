

#include "inventory.h";

namespace ExolorGame {
    class BankAccount;

    class Character {

    private:
        std::string name;
        BankAccount* bank;
        std::shared_ptr<Inventory> inventory;

    public:
        Character(std::string characterName, BankAccount* playerBank);

        Character(std::string characterName);

        const std::string& getName();

        std::shared_ptr<Inventory> getInventory();

        BankAccount* getBankAccount();

        void deposit(double amount);

        const bool withdraw(double amount);

        void displayBalance();
    };
}