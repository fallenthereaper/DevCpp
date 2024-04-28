
#include "src/core/shop/game_state.h"
#include "src/core/bank/bank_account.h"
#include "src/core/shop/game.h"
#include "src/core/shop/character.h"
ExolorGame::ShopState::ShopState(Game* game) : ExolorGame::GameMenu(game, "Shop Menu") {
    // Update logic for the menu state
}

void ExolorGame::ShopState::update(Game* game) {
    GameMenu::update(game);
}

void ExolorGame::ShopState::init(Game* game) {
    GameMenu::init(game);
}

void ExolorGame::ShopState::render(GameRenderer::TextCanvas* canvas) {
    GameMenu::render(canvas);


}

void ExolorGame::ShopState::initCommands() {
    GameMenu::initCommands();

    GameRenderer::TextCanvas* canvas = getGame()->getCanvas();

    addCommand("buy", [canvas](Game* g, InputParameter param) {
        std::string errorMessage = "Buy Item";
        

        if (g->getCharacter() == nullptr) {
            std::cout << "No character available to buy items." << std::endl;
            return;
        }

        ExolorGame::Character* character = g->getCharacter();
        ExolorGame::Inventory* inventory = character->getInventory();

        if (param.size() >= 1) {
            std::string itemName = param[0];
            int count = 1;
            if (param.size() >= 2) {
                count = std::stoi(param[1]); // Convert second parameter to integer (item count)
            }

            BankAccount* bankAccount = character->getBankAccount();
            double balance = bankAccount->getBalance();
            Item* selectedItem = ItemRegistry::getInstance()->getItem(itemName);

            if (selectedItem == nullptr) {
                errorMessage = "Invalid Item";
             //   std::cout << "Invalid Item" << std::endl;
                return;
            }

            int itemPrice = selectedItem->getPrice();
            int totalCost = itemPrice * count;

            if (balance < totalCost) {
                std::ostringstream msg;
                msg << "Insufficient funds to buy " << count << " " << itemName << ".";

                errorMessage = msg.str();
              //  std::cout << "Insufficient funds to buy " << count << " " << itemName << "." << std::endl;
      
            }

            // Add purchased items to the character's inventory
            if (bankAccount->withdraw(totalCost)) {
                if (inventory->insertItem(new ItemStack( selectedItem, count))) { //todo remove from the shop
                    std::ostringstream msg;
                    msg << "Successfully bought " << count << " " << itemName << " for " << totalCost << " gold.";
                    errorMessage = msg.str();

                }
              
              //  std::cout << "Successfully bought " << count << " " << itemName << " for " << totalCost << " gold." << std::endl;
            }


            canvas->drawSquare(Vec2(( canvas->getWidth()- errorMessage.length() ) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
        }
        });

    addCommand("inventory", [canvas](Game* g, InputParameter param) {
        g->setGameState(new InventoryState(g));
        });
    addCommand("show", [canvas](Game* g, InputParameter param) {

        canvas->clear();
    

        const auto& itemMap = ItemRegistry::getInstance()->getItemMap();


        Vec2 shopTopLeft(16, 3);
        int maxWidth = 6; // Maximum items per row
        int itemWidth = 18;
        int itemHeight = 3;
        int maxItemCount = 30; // Maximum items to display

        displayItemList(canvas, itemMap, "Item Shop", shopTopLeft, maxWidth, itemWidth, itemHeight, maxItemCount);
        });


}