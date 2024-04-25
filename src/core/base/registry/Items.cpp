#pragma once

#include "src/core/shop/registry/items.h"
#include "src/core/shop/item.h"

namespace ShopGame {
    using ItemSupplier = std::function<Item* ()>;

   const auto registry = ItemRegistry::getInstance();


   static const ItemSupplier APPLE = registerItemBuilder("apple", 5.0f);
   static const ItemSupplier IRON_SWORD = registerItemBuilder("iron_sword", 30.0f);
   static const ItemSupplier POTION_HEALTH = registerItemBuilder("potion_health", 20.0f, "Heals the user");
   static const ItemSupplier PICKAXE = registerItemBuilder("pickaxe", 10.0f);
   static const ItemSupplier TORCH = registerItemBuilder("torch", 10.0f);
   static const ItemSupplier BOW = registerItemBuilder("bow", 20.0f);
   static const ItemSupplier SHIELD = registerItemBuilder("shield", 15.0f);
   static const ItemSupplier DIAMOND = registerItemBuilder("diamond", 100.0f);
   static const ItemSupplier BREAD = registerItemBuilder("bread", 2.0f);
   static const ItemSupplier ARMOR_SET = registerItemBuilder("armor_set", 40.0f);

   
   static ItemSupplier ShopGame::registerItemBuilder(const std::string& name, float price, const std::string& description) {
       auto registry = ItemRegistry::getInstance();
       return registry->registerItem(name, [name, price, description]() -> Item* { return new Item(name, price, description); });
   }

   void ShopGame::registerItems() {
    
   }

    

} // namespace ShopGame