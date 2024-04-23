#pragma once
#include <vector>
#include "ItemStack.h"
#include <iostream>
#include "src/core/utils/containers.h"


namespace ShopGame {

    class Inventory {
    public:
        // Constructor to initialize an empty inventory
        Inventory(int pSize) : size(pSize) {};

        // Destructor to clean up resources (deletes all item stacks)
        ~Inventory();

        // Add an item stack to the inventory
        void insertItem(ItemStack* itemStack);

        // Remove an item stack from the inventory (and delete it)
        void extractItem(ItemStack* itemStack);

        // Get the total number of item stacks in the inventory
        int getItemCount() const;

        // Get an item stack at a specific index
        ItemStack* getItem(int index) const;

        // Clear the inventory (delete all item stacks)
        void clear();

        const int getSize() const;

        // Add a change listener function
        void addChangeListener(const std::function<void(Inventory*)>& listener);

        void notifyListeners();

    private:
        int size;
        std::vector<ItemStack*> itemStacks; 
        std::vector<std::function<void(Inventory*)>> changeListeners; 
    };

} // namespace ShopGame