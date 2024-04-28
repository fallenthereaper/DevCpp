#include "src/core/shop/character.h"
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include "src/core/shop/inventory.h"
#include "src/core/utils/utility.h" // Include utility for parsing commands

ExolorGame::InventoryState::InventoryState(Game* game) : ExolorGame::GameMenu(game, "Inventory Menu"), inventory(new ExolorGame::Inventory(18)) {
    
}

void ExolorGame::InventoryState::update(Game* game) {
   
}

void ExolorGame::InventoryState::init(Game* game) {
    GameMenu::init(game);
}

void ExolorGame::InventoryState::render(GameRenderer::TextCanvas* canvas) {
    GameMenu::render(canvas);
}

ExolorGame::Inventory* ExolorGame::InventoryState::getInventory() {
    return inventory;
}
void displayErrorMessage(GameRenderer::TextCanvas* canvas, const std::string& message) {
    canvas->drawSquare(Vec2((canvas->getWidth() - message.length()) / 2, 10), message.length() + 2, 5, '*', message, true);
}

// Helper function to handle invalid command parameters
bool handleInvalidParameters(GameRenderer::TextCanvas* canvas, const std::string& errorMessage) {
    displayErrorMessage(canvas, errorMessage);
    return false; // Return false to indicate failure
}

// Helper function to handle insufficient funds
bool handleInsufficientFunds(GameRenderer::TextCanvas* canvas, const std::string& itemName, int requiredAmount) {
    std::ostringstream msg;
    msg << "Insufficient funds to buy " << requiredAmount << " " << itemName << ".";
    displayErrorMessage(canvas, msg.str());
    return false; // Return false to indicate failure
}
void handleSuccessMessage(GameRenderer::TextCanvas* canvas, const std::string& successMessage) {
    displayErrorMessage(canvas, successMessage);
}
void ExolorGame::InventoryState::initCommands() {
    GameMenu::initCommands();

    GameRenderer::TextCanvas* canvas = getGame()->getCanvas();

    addCommand("bank", [canvas](Game* g, InputParameter& param) {
        canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Bank Menu", true);
        });


    addCommand("sell", [canvas](Game* g, InputParameter& param) {
        std::string errorMessage;

        canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Sell Item", true);

        if (g->getCharacter() == nullptr) {
            errorMessage = "No character available to sell items.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        ExolorGame::Character* character = g->getCharacter();
        ExolorGame::Inventory* inventory = character->getInventory();
        BankAccount* bankAccount = character->getBankAccount();

        if (inventory == nullptr || bankAccount == nullptr) {
            errorMessage = "Inventory or bank account is not available.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        if (param.size() < 2) {
            errorMessage = "Invalid sell command usage. Usage: sell <itemName> <count>";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        std::string itemName = param[0];
        std::string countStr = param[1];

        int count;
        try {
            count = std::stoi(countStr); 
        }
        catch (const std::invalid_argument& e) {
            errorMessage = "Invalid count parameter: " + std::string(e.what());
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        if (count <= 0) {
            errorMessage = "Invalid count parameter. Count must be a positive integer.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        // Retrieve the item from the inventory (not from the registry)
        Item* itemToSell = nullptr;
        for (ItemStack* stack : inventory->getSlots()) {
            if (stack && stack->getItem() && stack->getItem()->getName() == itemName) {
                itemToSell = stack->getItem();
                break;
            }
        }

        if (itemToSell == nullptr) {
            errorMessage = "Item '" + itemName + "' not found in the inventory.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        // Check if the item quantity is sufficient for selling
        int availableQuantity = inventory->getItemCount(itemToSell);
        if (availableQuantity < count) {
            errorMessage = "Insufficient quantity of '" + itemName + "' in the inventory.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        // Calculate the total sale price
        int itemPrice = itemToSell->getPrice();
        int totalSalePrice = itemPrice * count;

        // Remove the sold items from the inventory
        int remainingItems = inventory->removeItem(itemToSell, count);

        // Deposit the sale proceeds into the character's bank account
        bankAccount->deposit(totalSalePrice);


        std::ostringstream msg;
        msg << "Sold " << count << " " << itemName << " for " << totalSalePrice << " gold.";
        errorMessage = msg.str();
        canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
        });
    addCommand("show", [canvas](Game* g, InputParameter& param) {
        std::cout << "Opening Inventory..." << std::endl;

        if (g->getCharacter() == nullptr) {
            std::cout << "No character available to access inventory." << std::endl;
            return;
        }

        ExolorGame::Inventory* inventory = g->getCharacter()->getInventory();
        if (inventory == nullptr) {
            std::cout << "Character's inventory is not available." << std::endl;
            return;
        }

        const std::vector<ItemStack*>& items = inventory->getSlots();

        if (items.empty()) {
            std::cout << "Inventory is empty." << std::endl;
        }
        else {
            std::cout << "Inventory Contents:" << std::endl;
            for (const ItemStack* item : items) {
                std::cout << "- " << item->getItem()->getName() << std::endl;
                std::cout << " (Count: " << item->getCount() << ")";
                // Add more details as needed (e.g., item properties, quantity, etc.)
            }
        }


        Vec2 shopTopLeft(16, 3);
        int maxWidth = 6; // Maximum items per row
        int itemWidth = 18;
        int itemHeight = 3;
        int maxItemCount = 30; // Maximum items to display

    //    renderItems(canvas, inventory->getSlots(), "Inventory", shopTopLeft, maxWidth, itemWidth, itemHeight, maxItemCount);
        });
 
    addCommand("select", [this](Game* g, const InputParameter& param) {
   
        if (param.size() == 1) {
            std::string itemName = param[0];
            Item* selectedItem = nullptr;

            // Try to find the item by name
            selectedItem = ItemRegistry::getInstance()->getItem(itemName);

            if (selectedItem != nullptr) {
                GameRenderer::TextCanvas* canvas = g->getCanvas();
                std::string itemName = selectedItem->getName();

                // Calculate the required dimensions for the square
                int width = itemName.length() + 4; // Width of the square (item name + padding)
                int height = 5; // Height of the square

                // Draw a square with item information
                canvas->drawSquare({ 8, 2 }, width, height, '*', "Selected Item", true);
                canvas->drawText({ 8, 8 }, itemName); // Display item name within the square
            }
            else {
                std::cout << "Item not found." << std::endl;
            }
        }
       
        });
     }



