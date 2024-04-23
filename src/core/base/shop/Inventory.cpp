#include "src/core/shop/Inventory.h"


namespace ShopGame {


    Inventory::~Inventory() {
        clear(); // Cleanup resources in destructor
    }

    void Inventory::insertItem(ItemStack* itemStack) {
        itemStacks.push_back(itemStack);
        notifyListeners(); // Notify listeners upon change
    }

    void Inventory::extractItem(ItemStack* itemStack) {
        auto it = std::find(itemStacks.begin(), itemStacks.end(), itemStack);
        if (it != itemStacks.end()) {
            itemStacks.erase(it);
            delete itemStack; // Delete the removed item stack
            notifyListeners(); // Notify listeners upon change
        }
    }

    int Inventory::getItemCount() const {
        return itemStacks.size();
    }
    

    const int Inventory::getSize() const {
        return size;
      }

    ItemStack* Inventory::getItem(int slot) const {
        if (slot >= 0 && slot < itemStacks.size()) {
            return itemStacks[slot];
        }
        return nullptr;
    }

    void Inventory::clear() {
        for (auto itemStack : itemStacks) {
            delete itemStack;
        }
        itemStacks.clear();
        notifyListeners(); // Notify listeners upon change
    }

    void Inventory::addChangeListener(const std::function<void(Inventory*)>& listener) {
        changeListeners.push_back(listener);
    }

    void Inventory::notifyListeners() {
        for (auto listener : changeListeners) {
            listener(this);
        }
    }

} // namespace ShopGame