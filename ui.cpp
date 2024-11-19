#include "ui.h"
#include <iostream>
#include <iomanip>
#include "inventory.h"


using namespace std;

void showInventoryMenu(const Inventory& inventory) {
    inventory.showInventory();
}

void displayFinalStats(int score, long long duration) {
    cout << "\nFinal Stats:\n";
    cout << "Score: " << score << endl;
    cout << "Time Taken: " << duration << " seconds\n";
    printStars();
}

void printStars() {
    cout << "\n*****************************************\n";
}
