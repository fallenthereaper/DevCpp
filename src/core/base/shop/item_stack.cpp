#include "src/core/shop/item_stack.h"
#include <iostream>
#include <cstddef>  // Include for std::byte

namespace ShopGame {

    ItemStack::ItemStack(Item* item, std::byte quantity) : item(item), count(quantity) {}

    Item* ItemStack::getItem() const {
        return item;
    }

    std::byte ItemStack::getCount() const {
        return count;
    }

    void ItemStack::setCount(int newQuantity) {
        count = static_cast<std::byte>(newQuantity);
    }

    void ItemStack::increaseCount(int amount) {
        // Cast std::byte to unsigned char, perform arithmetic, cast back
        auto current_count = static_cast<unsigned char>(count);
        count = static_cast<std::byte>(current_count + amount);
    }

    void ItemStack::decreaseCount(int amount) {
        // Cast std::byte to unsigned char, perform arithmetic, cast back
        auto current_count = static_cast<unsigned char>(count);
        count = static_cast<std::byte>(current_count - amount);
    }

} // namespace ShopGame