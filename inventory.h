
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "items.h"

class Inventory {
public:
    void addItem(const Item& item);
    void showInventory() const;
    bool hasItem(const std::string& itemName) const;
    bool useItem(const std::string& itemName);
private:
    std::vector<Item> items;
};

#endif // INVENTORY_H
