#include "src/core/shop/registry/ItemRegistry.h"
#include <stdexcept>  // Include this for std::runtime_error

namespace ShopGame {
    using Registry = std::unordered_map<std::string, std::function<ShopGame::Item* ()>>;

    Registry ShopGame::ItemRegistry::items;
    ItemRegistry* ItemRegistry::instance = nullptr;

    ItemRegistry* ItemRegistry::getInstance() {
        if (instance == nullptr) {
            instance = new ItemRegistry();
        }
        return instance;
    }

    std::function<Item* ()> ItemRegistry::registerItem(const std::string& name, std::function<Item* ()> factory) {
        items.emplace(name, factory);
        return factory;
    }


    const std::unordered_map<std::string, ItemRegistry::ItemFactory>& ItemRegistry::getItemMap() const {
        return items; // Return a reference to the map of registered items
    }

    void ItemRegistry::listAllItems() const {
        for (const auto& itemPair : items) {
            Item* item = itemPair.second(); // Get the item by invoking the factory function
            std::cout << "Item: " << item->getName() << std::endl;
            delete item; // Clean up the item created for this listing
        }
    }

    Item* ItemRegistry::getItem(const std::string& name) const {
        auto it = items.find(name);
        if (it != items.end()) {
            return it->second();
        }

        std::cout << "Item '" + name + "' not registered.";
        return nullptr;
    }

}