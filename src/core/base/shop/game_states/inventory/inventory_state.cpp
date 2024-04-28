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

    std::vector<ItemStack*> itemStacks = inventory->getSlots();

    ExolorGame::Character* character = game->getCharacter();
    if (!character) {
        std::cout << "Error: No character available to access inventory." << std::endl;
        return;
    }

    ExolorGame::Inventory* inventory = character->getInventory();
    if (!inventory) {
        std::cout << "Error: Character's inventory is not available." << std::endl;
        return;
    }

    // Sort item stacks alphabetically by item name
    std::sort(itemStacks.begin(), itemStacks.end(), [](const ItemStack* a, const ItemStack* b) {
        if (a && b) {
            return a->getItem()->getName() < b->getItem()->getName();
        }
        return false;
        });
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
        bool sellAll = false;
        if (countStr == "all") {
            sellAll = true;
        }
        else {
            try {
                count = std::stoi(countStr);
            }
            catch (const std::invalid_argument& e) {
                errorMessage = "Invalid count parameter: " + std::string(e.what());
                canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
                return;
            }

            if (count <= 0) {
                errorMessage = "Invalid count parameter. Count must be a positive integer or 'all'.";
                canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
                return;
            }
        }



        // Retrieve the item from the inventory (not from the registry)
        Item* itemToSell = nullptr;

        if (sellAll) {
        count = inventory->getItemCount(itemToSell);
        if (count == 0) {
            errorMessage = "No '" + itemName + "' items to sell.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }
    }
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
            return;
        }
      
            std::cout << "Inventory Contents:" << std::endl;
            for (const ItemStack* itemStack : items) {
                if (itemStack && itemStack->getItem()) {
                    std::cout << "- " << itemStack->getItem()->getName() << std::endl;
                    std::cout << " (Count: " << itemStack->getCount() << ")" << std::endl;
                    // Add more details as needed (e.g., item properties, quantity, etc.)
                }
                else {
                    std::cout << "- Invalid item in inventory" << std::endl;
                }
            }
        

        // Calculate the total width of the inventory display
        int itemWidth = 18;
        int itemSpacing = 1; // Spacing between items
        int maxItemsPerRow = 6; // Maximum items per row
        int inventoryWidth = (itemWidth + itemSpacing) * std::min(static_cast<int>(items.size()), maxItemsPerRow);

        // Calculate the center position to properly center the inventory horizontally
        int canvasWidth = canvas->getWidth();
        Vec2 centerPosition(((canvasWidth - inventoryWidth) / 2) + 8, 5); // Center horizontally

        // Render inventory using canvas at the calculated center position
        std::cout << "Rendering inventory at position (" << centerPosition.x << ", " << centerPosition.y << ")" << std::endl;

        renderItems(canvas, items, "Inventory", centerPosition, maxItemsPerRow, itemWidth, 3, items.size());
        });
 
    addCommand("select", [this, canvas](Game* g, const InputParameter& param) {
        std::string errorMessage;

        if (g->getCharacter() == nullptr) {
            errorMessage = "No character available to access inventory.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        ExolorGame::Inventory* inventory = g->getCharacter()->getInventory();
        if (inventory == nullptr) {
            errorMessage = "Character's inventory is not available.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        if (param.size() != 1) {
            errorMessage = "Invalid select command usage. Usage: select <itemName>";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        std::string itemName = param[0];

        // Find the item in the inventory
        Item* selectedItem = ItemRegistry::getInstance()->getItem(itemName);
        if (selectedItem == nullptr) {
            errorMessage = "Item '" + itemName + "' not found in the registered.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
            return;
        }

        // Find the item stack for the selected item
        ItemStack* itemStack = inventory->findItemStack(selectedItem);
        if (itemStack == nullptr) {
            errorMessage = "Item '" + itemName + "' not found in the inventory.";
            canvas->drawSquare(Vec2((canvas->getWidth() - errorMessage.length()) / 2, 10), errorMessage.length() + 2, 5, '*', errorMessage, true);
         
        }

        // Clear canvas before rendering
     

        if (itemStack) {
            // Calculate the position to center the square and text
            int squareWidth = 40; // Adjust as needed
            int squareHeight = 15; // Adjust as needed
            Vec2 squareTopLeft((canvas->getWidth() - squareWidth) / 2, (canvas->getHeight() - squareHeight) / 2);

            // Render a big square as the background
            canvas->drawSquare(squareTopLeft, squareWidth, squareHeight, '*', "", true); // Background square

            // Render text inside the square
            canvas->drawText(Vec2(squareTopLeft.x + 2, squareTopLeft.y + 2), "Selected Item"); // Title
            canvas->drawText(Vec2(squareTopLeft.x + 2, squareTopLeft.y + 5), "Name: " + selectedItem->getName());
            canvas->drawText(Vec2(squareTopLeft.x + 2, squareTopLeft.y + 7), "Description: " + selectedItem->getDescription());

            // Get total count and price information
            int totalCount = itemStack->getCount();
            int itemPrice = selectedItem->getPrice();
            int totalPrice = totalCount * itemPrice;

            canvas->drawText(Vec2(squareTopLeft.x + 2, squareTopLeft.y + 9), "Total Count: " + std::to_string(totalCount));
            canvas->drawText(Vec2(squareTopLeft.x + 2, squareTopLeft.y + 11), "Price per Item: " + std::to_string(itemPrice));
            canvas->drawText(Vec2(squareTopLeft.x + 2, squareTopLeft.y + 13), "Total Price: " + std::to_string(totalPrice));

         
        }
  
        });
     }





