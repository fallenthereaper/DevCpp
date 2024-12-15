#pragma once
#include <vector>
#include "item_stack.h"
#include <iostream>
#include "src/core/utils/containers.h"

namespace ExolorGame {

    class Inventory {
    public:
         // Destructor to clean up resources (deletes all item stacks)
        ~Inventory();

        Inventory(int pSize);

        // Add an item stack to the inventory
        bool insertItem(ItemStack* itemStack);
        // Find an ItemStack containing a specific item
        ItemStack* findItemStack(const Item& item) const;
        // Remove an item stack from the inventory (and delete it)
        void extractItem(ItemStack* itemStack);

        // Get the total number of item stacks in the inventory
        int getItemCount() const;

       const int getSize() const;

        // Get the maximum stack size supported by this inventory
        int getMaxStackSize() const;

        // Check if the inventory has empty slots
        bool hasEmptySlot() const;

        // Find the first empty slot in the inventory
        int findEmptySlot() const;

        // Find the first slot containing a specific item
        int findItemSlot(Item* item) const;

        // Add a specific quantity of an item to the inventory
        // Returns the amount of items that couldn't be added (due to space constraints)
        int addItem(Item* item, int quantity);

        
        // Get the item stack at a specific slot index
           ItemStack* getItem(int slot) const;

        // Remove a specific quantity of an item from the inventory
        // Returns the amount of items that couldn't be removed (due to insufficient quantity)
        int removeItem(Item* item, int quantity);

        // Swap items between two slots in the inventory
        void swapItems(int slot1, int slot2);

        void clear();
        // Get the total number of stacks containing a specific item
        int getItemCount(Item* item) const;
        // Add a change listener function
        void addChangeListener(const std::function<void(Inventory*)>& listener);

        void notifyListeners();

        std::vector<ItemStack*> getSlots();


    private:
        int size;
        std::vector<ItemStack*> slots; 
        std::vector<std::function<void(Inventory*)>> changeListeners; 
        // Private helper function to find the first slot containing a nullptr (empty slot)
        int findEmptySlotInternal() const;
    };

} // namespace ShopGame