#include "src/core/shop/item_stack.h"
#include <iostream>
#include <cstddef>  // Include for std::byte
#include <cmath>
namespace ExolorGame {

    ItemStack::ItemStack(Item* item, int quantity) : item(item), count(quantity) {}

    Item* ItemStack::getItem() const {
        return item;
    }

    int ItemStack::getCount() const {
        return count;
    }

    void ItemStack::setCount(int newQuantity) {
        count = std::min(std::max(newQuantity, 0), getMaxStackSize());
    }

    void ItemStack::increaseCount(int amount) {
        if (amount > 0) {
            int maxStackSize = getMaxStackSize();
            int newCount = std::min(count + amount, maxStackSize);
            setCount(newCount);
        }
    }

    void ItemStack::decreaseCount(int amount) {
        if (amount > 0) {
            int newCount = std::max(count - amount, 0);
            setCount(newCount);
        }
    }

    int ItemStack::getMaxStackSize() const {
       
        return 16;
    }



} // namespace ShopGame