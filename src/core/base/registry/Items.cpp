#pragma once

#include "src/core/shop/registry/Items.h"
#include "src/core/shop/Item.h"

namespace ShopGame {

    
    void ShopGame::registerItems() {
        auto registry = ItemRegistry::getInstance();
        registry->registerItem("iron_sword", []() -> Item* { return new Item("Iron Sword", 30.0f); });
        registry->registerItem("apple", []() -> Item* { return new Item("Apple", 5.0f); });
        registry->registerItem("potion_health", []() -> Item* { return new Item("Health Potion", 20.0f, "Heals the user"); });
        registry->registerItem("pickaxe", []() -> Item* { return new Item("Pickaxe", 10.0f); });
        registry->registerItem("torch", []() -> Item* { return new Item("Torch", 10.0f); });
        registry->registerItem("bow", []() -> Item* { return new Item("Bow", 20.0f); });
        registry->registerItem("shield", []() -> Item* { return new Item("Shield", 15.0f); });
        registry->registerItem("diamond", []() -> Item* { return new Item("Diamond", 100.0f); });
        registry->registerItem("bread", []() -> Item* { return new Item("Bread", 2.0f); });
        registry->registerItem("armor_set", []() -> Item* { return new Item("Armor Set", 40.0f); });
    }

} // namespace ShopGame