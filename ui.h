#ifndef UI_H
#define UI_H

#include "inventory.h"

void showInventoryMenu(const Inventory& inventory);
void displayFinalStats(int score, long long duration);
void printStars();

#endif // UI_H
