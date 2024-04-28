#pragma once

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class ItemStack;

namespace ExolorGame {
  class Item {

  private:
      short id;
      std::string name;
      std::string description;
      double price;


  public:
      static Item* undefined() {
          static Item notDefined("NOT_DEFINED", 0, " "); // Placeholder item with name "NOT_DEFINED" and price 0
          return &notDefined;
      }

    public:
        Item(const std::string& name, double price, const std::string& description);
        Item(const std::string& name, double price);
       const std::string getName() const;

       const std::string getDescription() const;
       bool operator==(const Item& other) const {
           // Compare based on item name and price
           return (name == other.name);
       }

       const double getPrice() const;

  };

}

#endif