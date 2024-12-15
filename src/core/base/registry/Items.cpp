#include "src/core/shop/registry/items.h"


    using ItemSupplier = std::function<ExolorGame::Item* ()>;

   const auto registry = ExolorGame::ItemRegistry::getInstance();


 

  // static const ItemSupplier DIAMOND_PICKAXE = registerItemBuilder("diamond_pickaxe", 20.0f);
  // static const ItemSupplier DIAMOND_SWORD = registerItemBuilder("diamond_sword", 30.0f);
  
  // static const ItemSupplier DIAMOND_HOE = registerItemBuilder("diamond_hoe", 15.0f);
  // static const ItemSupplier DIAMOND_AXE = registerItemBuilder("diamond_axe", 15.0f);


   


   void ExolorGame::registerItems() {
       const ItemSupplier APPLE = registerItemBuilder("apple", 5.0f);
       const ItemSupplier SWORD = registerItemBuilder("sword", 30.0f);
       const ItemSupplier POTION_HEALTH = registerItemBuilder("potion_health", 20.0f, "Heals the user");
       static const ItemSupplier PICKAXE = registerItemBuilder("pickaxe", 10.0f);
       static const ItemSupplier AXE = registerItemBuilder("axe", 10.0f);
       static const ItemSupplier TORCH = registerItemBuilder("torch", 10.0f);
       static const ItemSupplier BOW = registerItemBuilder("bow", 20.0f);
       static const ItemSupplier SHIELD = registerItemBuilder("shield", 15.0f);
       static const ItemSupplier DIAMOND = registerItemBuilder("diamond", 250.0f);
       static const ItemSupplier BREAD = registerItemBuilder("bread", 2.0f);
       static const ItemSupplier ARMOR_SET = registerItemBuilder("armor_set", 40.0f);
       static const ItemSupplier HOE = registerItemBuilder("hoe", 15.0f);

       static const ItemSupplier IRON_PICKAXE = registerItemBuilder("iron_pickaxe", 20.0f);
       static const ItemSupplier IRON_SWORD = registerItemBuilder("iron_sword", 30.0f);
       static const ItemSupplier IRON_HOE = registerItemBuilder("iron_hoe", 15.0f);
       static const ItemSupplier IRON_AXE = registerItemBuilder("iron_axe", 15.0f);

       static const ItemSupplier GOLD_PICKAXE = registerItemBuilder("gold_pickaxe", 20.0f);
       static const ItemSupplier GOLD_SWORD = registerItemBuilder("gold_sword", 30.0f);
       static const ItemSupplier GOLD_HOE = registerItemBuilder("gold_hoe", 15.0f);
       static const ItemSupplier GOLD_AXE = registerItemBuilder("gold_axe", 15.0f);
   }
