#include "src/core/shop/inventory.h"


namespace ShopGame {


    Inventory::~Inventory() {
        clear(); // Cleanup resources in destructor
    }

    void Inventory::insertItem(ItemStack* itemStack) {
        slots.push_back(itemStack);
        notifyListeners(); // Notify listeners upon change
    }

    void Inventory::extractItem(ItemStack* itemStack) {
        auto it = std::find(slots.begin(), slots.end(), itemStack);
        if (it != slots.end()) {
            slots.erase(it);
            delete itemStack; // Delete the removed item stack
            notifyListeners(); // Notify listeners upon change
        }
    }

    int Inventory::getItemCount() const {
        return slots.size();
    }
    

    const int Inventory::getSize() const {
        return size;
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

    void Inventory::notifyListeners() {
        for (auto listener : changeListeners) {
            listener(this);
        }
    }

} // namespace ShopGame