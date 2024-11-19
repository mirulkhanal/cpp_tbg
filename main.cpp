#include <iostream>
#include "game_state.h"
#include "inventory.h"
#include "ui.h"
#include "story.h"

int main() {
    Inventory inventory;
    GameState currentState = GameState::START;

    while (currentState != GameState::WIN) {
        handleGameState(currentState, inventory);
    }

    std::cout << "\nYou have won the game!" << std::endl;
    return 0;
}
