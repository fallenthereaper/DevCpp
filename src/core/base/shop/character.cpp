#include "src/core/shop/character.h"
#include "src/core/bank/bank_account.h";

    // Constructor with bank account
    ExolorGame::Character::Character(std::string characterName, BankAccount* playerBank)
        : name(characterName), bank(playerBank), inventory(std::make_shared<Inventory>(18)) {
    }

    // Constructor without bank account
    ExolorGame::Character::Character(std::string characterName) : Character(characterName, nullptr) {

    }
        
  

    const std::string& ExolorGame::Character::getName() {
        return name;
    }

    std::shared_ptr<ExolorGame::Inventory> ExolorGame::Character::getInventory() {
        return inventory;
    }

    ExolorGame::BankAccount* ExolorGame::Character::getBankAccount() {
        return bank;
    }

    void ExolorGame::Character::deposit(double amount) {
      
    }

    const bool ExolorGame::Character::withdraw(double amount) {
        if (bank) {
              
        }
        return false;
    }

    void ExolorGame::Character::displayBalance() {
        if (bank) {
     
        }
    }

