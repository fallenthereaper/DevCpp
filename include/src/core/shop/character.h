
#include "src/core/bank/bank_account.h";
#include "inventory.h";

namespace ShopGame {

    class Character {

    private:
        std::string name;
        BankAccount* bank;
        std::shared_ptr<Inventory> inventory;

    public:
        Character(const std::string& characterName, BankAccount& playerBank);

        const std::string& getName();

        std::shared_ptr<Inventory> getInventory();

        BankAccount* getBankAccount();

        void deposit(double amount);

        const bool withdraw(double amount);

        void displayBalance();
    };
}