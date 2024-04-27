#include "src/core/shop/character.h"


    // Constructor with bank account
    ExolorGame::Character::Character(std::string characterName, BankAccount* playerBank)
        : name(characterName), bank(playerBank), inventory(std::make_shared<Inventory>(18)) {
    }

    // Constructor without bank account
    ExolorGame::Character::Character(std::string characterName, int balance, int accountId) : Character(characterName, new BankAccount(characterName, balance,accountId )) {

    }
        
  

    const std::string& ExolorGame::Character::getName() {
        return name;
    }

    std::shared_ptr<ExolorGame::Inventory> ExolorGame::Character::getInventory() {
        return inventory;
    }

    BankAccount* ExolorGame::Character::getBankAccount() {
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

