#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <conio.h>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <functional>
#include "src/core/utils/utility.h"
#include "src/core/shop/game.h"


namespace ExolorGame {
   inline void displayItemList(GameRenderer::TextCanvas *canvas,
                         const std::unordered_map<std::string, ExolorGame::ItemRegistry::ItemFactory> &itemList,
                         const std::string &displayTitle, const Vec2 &topLeft, int maxWidth, int itemWidth,
                         int itemHeight, int maxItemCount) {
        int itemCount = std::min(static_cast<int>(itemList.size()), maxItemCount);

        // Calculate the number of rows needed based on the item count
        int numRows = (itemCount + (maxWidth - 1)) / maxWidth;
        int numCols = (itemCount + numRows - 1) / numRows;

        // Draw the title of the item list
        canvas->drawSquare(topLeft + Vec2{2, -1}, itemWidth * numRows + 3, itemHeight, '*', displayTitle, true);

        int row = topLeft.y + 2; // Start rendering items below the title
        int col = topLeft.x + 2;

        int itemIndex = 0;
        for (const auto &itemPair: itemList) {
            if (itemIndex >= maxItemCount) {
                break; // Stop rendering if maximum item count is reached
            }

            // Check if we need to move to the next row
            if (col + itemWidth > topLeft.x + numCols * itemWidth) {
                col = topLeft.x + 2; // Reset column position to start a new row
                row += itemHeight; // Move to the next row
            }

            // Get the item name from the item pair
            std::string itemName = itemPair.first;

            // Render the item at the current position
            canvas->drawSquare(Vec2(col, row + 1), itemWidth, itemHeight, '*', itemName, true);

            // Move to the next column position
            col += itemWidth + 1;

            ++itemIndex;
        }
    }


   inline void renderItems(GameRenderer::TextCanvas *canvas,
                     const std::vector<ExolorGame::ItemStack*> &itemList,
                     const std::string &displayTitle,
                     const Vec2 &topLeft,
                     int maxWidth,
                     int itemWidth,
                     int itemHeight,
                     int maxItemCount) {
        // Limit the number of items to render based on the maximum allowed
        int itemCount = std::min(static_cast<int>(itemList.size()), maxItemCount);

        // Determine the number of rows and columns needed
        int numCols = std::min(maxWidth, itemCount); // Columns are limited by maxWidth or the total number of items
        int numRows = (itemCount + numCols - 1) / numCols; // Calculate rows using ceiling logic

        // Draw the title of the item list (optional, commented out for now)
        // canvas->drawSquare(topLeft + Vec2{2, -1}, numCols * itemWidth + 3, itemHeight, '*', displayTitle, true);

        // Initial rendering position starts below the title
        int row = topLeft.y + 2; // Vertical offset for the first row
        int col = topLeft.x + 2; // Horizontal offset for the first column

        // Iterate over each item to render
        for (int itemIndex = 0; itemIndex < itemCount; ++itemIndex) {
            // Check if we've reached the column limit and need to move to the next row
            if (col + itemWidth > topLeft.x + numCols * itemWidth) {
                col = topLeft.x + 2;  // Reset to the first column
                row += itemHeight;    // Move down to the next row
            }

            // Get the current item stack (can be nullptr for empty slots)
            ExolorGame::ItemStack *itemStack = itemList[itemIndex];

            // Render an empty item slot at the current position
            canvas->drawSquare(Vec2(col, row), itemWidth, itemHeight, '*', "", true);

            // If the slot contains an item, display its name and count
            if (itemStack != nullptr) {
                std::string itemName = itemStack->getItem()->getName(); // Get item name
                int stackCount = itemStack->getCount();                 // Get item count

                // Create display string for the item slot (e.g., "ItemName x10")
                std::string itemDisplay = itemName + " x" + std::to_string(stackCount);

                // Render the item details inside the slot
                canvas->drawSquare(Vec2(col, row), itemWidth, itemHeight, '*', itemDisplay, true);
            }

            // Move to the next column position for the next item
            col += itemWidth + 1; // Add 1 for spacing between slots
        }
    }
    enum class Type : int {
        BASE, MENU, SHOP, INVENTORY, CHARACTER_SELECT, QUIT_GAME
    };

    class Game;

    class Inventory;

    using InputParameter = std::vector<std::string> &;

    using InputFunction = std::function<void(Game *, const InputParameter &)>;

    using InputMap = std::unordered_map<std::string, InputFunction>;

    class GameMenu {

    public:
        GameMenu(ExolorGame::Game *game, std::string name);

        ~GameMenu() = default;

        void handleInput(Game *game, const std::string &input);

        virtual void update(ExolorGame::Game *game) = 0;

        virtual void initCommands() = 0;

        virtual void init(ExolorGame::Game *game);

        void addCommand(const std::string &command, const InputFunction function);

        ExolorGame::Game *getGame();

        std::string getName();

        virtual void render(GameRenderer::TextCanvas *canvas) = 0;

        void nextPage();

        void prevPage();

        void setCurrentPage(int page);

    protected:
        int currentPage;
        int totalPages;
        std::string stateName;
        ExolorGame::Game *game;
        InputMap commandMap; //FOR PARAMETERS
    };

    class MenuState : public GameMenu {
    public:
        MenuState(Game *game);

        void initCommands() override;

        void update(Game *game) override;

        void init(Game *game) override;

        void render(GameRenderer::TextCanvas *canvas) override;
    };

    class ShopState : public GameMenu {
    public:
        ShopState(Game *game);

        void initCommands() override;

        void update(Game *game) override;

        void init(Game *game) override;

        void render(GameRenderer::TextCanvas *canvas) override;
    };

    class QuitGameState : public GameMenu {
    public:
        QuitGameState(Game *game);

        void initCommands() override;

        void update(Game *game) override;

        void init(Game *game) override;

        void render(GameRenderer::TextCanvas *canvas) override;
    };

    class InventoryState : public GameMenu {
    private:
        Inventory *inventory;
    public:
        InventoryState(Game *game);

        void initCommands() override;

        void update(Game *game) override;

        void init(Game *game) override;

        void render(GameRenderer::TextCanvas *canvas) override;

        Inventory *getInventory();
    };

    class SelectedItemState : public GameMenu {
    private:
        InventoryState *parentState;
    public:
        SelectedItemState(InventoryState *parentState);

        void initCommands() override;

        void update(Game *game) override;

        void init(Game *game) override;

        void render(GameRenderer::TextCanvas *canvas) override;

    };

    class Character;

    class CharacterSelectState : public GameMenu {
    protected:
        std::vector<ExolorGame::Character *> characters;
        int selectedCharacterIndex; // Index of currently selected character
    public:
        CharacterSelectState(Game *game);

        void initCommands() override;

        void update(Game *game) override;

        void init(Game *game) override;

        void render(GameRenderer::TextCanvas *canvas) override;

        void selectCharacter(int index);

        void addCharacter(const Character &character);

    };

} // namespace ShopGam

#endif