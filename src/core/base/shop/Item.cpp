#include "src/core/shop/item.h"

namespace ExolorGame {

	Item::Item(const std::string& pName, double pPrice, const std::string& pDescription) : name(pName), price(pPrice), description(pDescription) { }

	

	Item::Item(const std::string & pName, double pPrice) : Item(pName, pPrice, "") {

	}

	const std::string Item::getName() const {
		return name;
	}

	const std::string Item::getDescription() const {

		return description;
	}

	const double Item::getPrice() const {

		return price;
	}
}