#pragma once

#include "src/core/shop/registry/item_registry.h"

namespace ExolorGame {

    // Function to register predefined items with the ItemRegistry
    void registerItems();

    inline auto registerItemBuilder(const std::string& name, float price, const std::string& description = "") -> std::function<Item* ()> {
        auto registry = ItemRegistry::getInstance();
        return registry->registerItem(name, [name, price, description]() -> Item* { return new Item(name, price, description); });
    }
   

} // namespace ShopGame