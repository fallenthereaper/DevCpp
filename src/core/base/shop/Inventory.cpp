#include "src/core/shop/inventory.h"

class ItemStack;

namespace ExolorGame {

    //g
    Inventory::Inventory(int pSize) : size(pSize) {
        slots = std::vector<ItemStack*>(pSize, nullptr);
       // slots.reserve(pSize);
    }

    // Destructor implementation
    Inventory::~Inventory() {
        clear(); // Cleanup resources in destructor
    }

    // Add an item stack to the inventory
    bool Inventory::insertItem(ItemStack* itemStack) {
        if (!itemStack) {
            return false; // Do nothing if itemStack is nullptr
        }


        Item* item = itemStack->getItem();
        int count = itemStack->getCount();

        if (!item || count <= 0) {
            delete itemStack; // Delete the invalid itemStack
            return false;
        }
      

        // Try to stack the item with existing stacks in the inventory
        bool addedToStack = false;

        for (ItemStack* stack : slots) {
            if (stack && stack->getItem() == item) {
                int maxStackSize = stack->getMaxStackSize();
                int currentCount = stack->getCount();

                if (currentCount < maxStackSize) {
                    // Calculate how much more can be added to this stack
                    int spaceLeft = maxStackSize - currentCount;
                    int addAmount = std::min(count, spaceLeft);

                    stack->setCount(currentCount + addAmount);
                    count -= addAmount;

                    if (count <= 0) {
                        addedToStack = true;
                        break; // All items have been added to existing stack
                    }
                }
            }
        }

        // If there are remaining items to be added, create new stacks if possible
        while (count > 0 && hasEmptySlot()) { //FIXES unorganized stack, emprtry sçopt
            int index = findEmptySlot();
            ItemStack* newStack = new ItemStack(item, 0); // Create a new item stack
            int maxStackSize = newStack->getMaxStackSize();
            int addAmount = std::min(count, maxStackSize);

            newStack->setCount(addAmount);
            slots[index] = newStack;

            count -= addAmount;
     
        }

        delete itemStack; // Delete the original itemStack after processing
        notifyListeners(); // Notify listeners upon change
        return false;
    }

    // Remove an item stack from the inventory (and delete it)
    void Inventory::extractItem(ItemStack* itemStack) {
        auto it = std::find(slots.begin(), slots.end(), itemStack);
        if (it != slots.end()) {
            slots.erase(it);
            delete itemStack; // Delete the removed item stack
            notifyListeners(); // Notify listeners upon change
        }
    }

    // Get the total number of item stacks in the inventory
    int Inventory::getItemCount() const {
        return slots.size();
    }

    // Get the maximum stack size supported by this inventory
    int Inventory::getMaxStackSize() const {
   
        return 16; 
    }

    // Check if the inventory has empty slots
    bool Inventory::hasEmptySlot() const {
        return findEmptySlotInternal() != -1;
    }

    // Private helper function to find the first empty slot (nullptr)
    int Inventory::findEmptySlotInternal() const {
        for (int i = 0; i < slots.size(); ++i) {
            if (slots[i] == nullptr) {
                return i;
            }
        }
        return -1; // No empty slot found, all full
    }

    // Find the first empty slot in the inventory
    int Inventory::findEmptySlot() const {
        return findEmptySlotInternal();
    }

    // Find the first slot containing a specific item
    int Inventory::findItemSlot(Item* item) const {
        auto it = std::find_if(slots.begin(), slots.end(), [item](ItemStack* stack) {
            return stack != nullptr && stack->getItem() == item;
            });
        return (it != slots.end()) ? std::distance(slots.begin(), it) : -1;
    }

    ItemStack* Inventory::findItemStack(const Item& item) const {
        ItemStack* selectedStack = nullptr;
        for (ItemStack* stack : slots) {
            if ((stack != nullptr) && stack->getItem() == &item) {
                selectedStack = stack;
            }
        }
        return selectedStack; // Item stack not found for the specified item
    }

    // Add a specific quantity of an item to the inventory
    int Inventory::addItem(Item* item, int quantity) {
        int remaining = quantity;

        while (remaining > 0 && hasEmptySlot()) {
            int emptySlot = findEmptySlotInternal();
            ItemStack* newItemStack = new ItemStack(item, 0); // Create a new item stack
            int stackSize = getMaxStackSize();

            // Calculate how much can be added to this stack
            int addAmount = std::min(stackSize, remaining);
            newItemStack->setCount(addAmount);

            // Insert the new item stack into the empty slot
            slots[emptySlot] = newItemStack;
            remaining -= addAmount;
        }

        return remaining; // Return any leftover items that couldn't be added
    }

    // Remove a specific quantity of an item from the inventory
    int Inventory::removeItem(Item* item, int quantity) {
        int remaining = quantity;

        while (remaining > 0) {
            int itemSlot = findItemSlot(item);
            if (itemSlot == -1) {
                break; // Item not found in inventory
            }

            ItemStack* itemStack = slots[itemSlot];
            int stackCount = static_cast<int>(itemStack->getCount());

            if (stackCount <= remaining) {
                // Remove the entire stack
                delete itemStack;
                slots[itemSlot] = nullptr;
                remaining -= stackCount;
            }
            else {
                // Remove part of the stack
                itemStack->decreaseCount(remaining);
                remaining = 0;
            }
        }

        return remaining; // Return any leftover items that couldn't be removed
    }

    // Swap items between two slots in the inventory
    void Inventory::swapItems(int slot1, int slot2) {
        if (slot1 >= 0 && slot1 < size && slot2 >= 0 && slot2 < size && slot1 != slot2) {
            std::swap(slots[slot1], slots[slot2]);
            notifyListeners(); // Notify listeners upon change
        }
    }

    ItemStack* Inventory::getItem(int slot) const {
        if (slot >= 0 && slot < slots.size()) {
            return slots[slot];
        }
        return nullptr;
    }

    void Inventory::clear() {
        for (auto itemStack : slots) {
            delete itemStack;
        }
        slots.clear();
        notifyListeners(); // Notify listeners upon change
    }

    void Inventory::addChangeListener(const std::function<void(Inventory*)>& listener) {
        changeListeners.push_back(listener);
    }
    int Inventory::getItemCount(Item* item) const {
        int totalCount = 0;

        for (ItemStack* stack : slots) {
            if (stack != nullptr && stack->getItem() == item) {
                totalCount += stack->getCount();
            }
        }

        return totalCount;
    }
    std::vector<ItemStack*> Inventory::getSlots() {
        return slots;
    }

    void Inventory::notifyListeners() {
        for (auto listener : changeListeners) {
            listener(this);
        }
    }

} // namespace ShopGame