#include "src/core/shop/registry/ItemRegistry.h"
#include "src/core/shop/Item.h"

// Register item types during static initialization
namespace {
    struct ItemRegistrar {
        ItemRegistrar() {
            ShopGame::ItemRegistry::registerItem("iron_sword", []() -> ShopGame::Item* { return new ShopGame::Item("Iron Sword", 30.0f); });
            ShopGame::ItemRegistry::registerItem("apple", []() -> ShopGame::Item* { return new ShopGame::Item("Apple", 5.0f); });
            ShopGame::ItemRegistry::registerItem("potion_health", []() -> ShopGame::Item* { return new ShopGame::Item("Health Potion", 20.0f, "Heals the user"); });
            ShopGame::ItemRegistry::registerItem("pickaxe", []() -> ShopGame::Item* { return new ShopGame::Item("Pickaxe", 10.0f); });
            ShopGame::ItemRegistry::registerItem("torch", []() -> ShopGame::Item* { return new ShopGame::Item("Torch", 10.0f); });
            ShopGame::ItemRegistry::registerItem("bow", []() -> ShopGame::Item* { return new ShopGame::Item("Bow", 20.0f); });
            ShopGame::ItemRegistry::registerItem("shield", []() -> ShopGame::Item* { return new ShopGame::Item("Shield", 15.0f); });
            ShopGame::ItemRegistry::registerItem("diamond", []() -> ShopGame::Item* { return new ShopGame::Item("Diamond", 100.0f); });
            ShopGame::ItemRegistry::registerItem("bread", []() -> ShopGame::Item* { return new ShopGame::Item("Bread", 2.0f); });
            ShopGame::ItemRegistry::registerItem("armor_set", []() -> ShopGame::Item* { return new ShopGame::Item("Armor Set", 40.0f); });
        }
    } itemRegistrar; // Static instance of ItemRegistrar
}