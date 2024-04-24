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

         static ItemRegistry* getInstance();

        // Register an item type with a unique identifier
         std::function<Item* ()> registerItem(const std::string& itemId, std::function<Item* ()> factory);

        // Create an instance of the item based on its identifier
         Item* getItem(const std::string& itemId) const;

         ItemRegistry(const ItemRegistry&) = delete;
         ItemRegistry& operator=(const ItemRegistry&) = delete;

         const std::unordered_map<std::string, ItemFactory>& getItemMap() const;

     
         void listAllItems() const;

    private:
        static std::unordered_map<std::string, ItemFactory> items;
        static ItemRegistry* instance;
        ItemRegistry() {} // Private constructor for singleton

        

    };

} // namespace ShopGame

#endif