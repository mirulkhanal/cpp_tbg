#include "inventory.h"
#include <iostream>

using namespace std;

void Inventory::addItem(const Item& item) {
    items.push_back(item);
    cout << "\nYou have obtained: " << item.name << endl;
}

void Inventory::showInventory() const {
    if (items.empty()) {
        cout << "\nYour inventory is empty.\n";
        return;
    }
    cout << "\nInventory:\n";
    for (const auto& item : items) {
        cout << "- " << item.name << ": " << item.description << endl;
    }
}

bool Inventory::hasItem(const string& itemName) const {
    for (const auto& item : items) {
        if (item.name == itemName) {
            return true;
        }
    }
    return false;
}

bool Inventory::useItem(const string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->name == itemName) {
            cout << "You used: " << it->name << endl;
            items.erase(it); // Remove the used item.
            return true;
        }
    }
    cout << "You don't have that item.\n";
    return false;
}
