#pragma once
#include "src/core/shop/item.h"  // Include the definition of Item

namespace ExolorGame {

    class ItemStack {
    public:
        ItemStack(Item* item, int quantity);

        Item* getItem() const;

        int getCount() const;

        void setCount(int newQuantity);

        void increaseCount(int amount);

        void decreaseCount(int amount);

       int getMaxStackSize() const;

    private:
        Item* item;   // Pointer to the item type
        int count; // Quantity of this item in the stack
    };

} // namespace ShopGame