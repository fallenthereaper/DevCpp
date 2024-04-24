#pragma once

#include "src/core/shop/registry/ItemRegistry.h"
#include "src/core/shop/Item.h"

namespace ShopGame {

    // Function to register predefined items with the ItemRegistry
    void registerItems();

    std::function<Item* ()> registerItemBuilder(const std::string& name, float price, const std::string& description = "");
   

} // namespace ShopGame