#pragma once

#ifndef ITEM_REGISTRY_H
#define ITEM_REGISTRY_H

#include <unordered_map>
#include <string>
#include <functional>
#include "src/core/shop/Item.h"


namespace ShopGame {

    // ItemRegistry class to manage registered item types
    class ItemRegistry {
    public:
        using ItemFactory = std::function<Item*()>;

        // Register an item type with a unique identifier
        static void registerItem(const std::string& itemId, ItemFactory creator) {
            getItemRegistry()[itemId] = creator;
        }

        // Create an instance of the item based on its identifier
        static Item* createItem(const std::string& itemId) {
            auto it = getItemRegistry().find(itemId);
            if (it != getItemRegistry().end()) {
                return it->second();
            }
            return nullptr;
        }

    private:
        // Static function to access the item registry map
        static std::unordered_map<std::string, ItemFactory>& getItemRegistry() {
            static std::unordered_map<std::string, ItemFactory> itemRegistry;
            return itemRegistry;
        }
    };

} // namespace ShopGame

#endif