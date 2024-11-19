#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <map>
#include "game_state.h"
#include "inventory.h"

enum class GameState {
    START,
    FOREST,
    CAVE,
    VILLAGE,
    LAKE,
    MOUNTAIN,
    END,
    WIN
};

using StateMap = std::map<GameState, std::map<char, GameState>>;

extern StateMap stateTransitions;
void handleGameState(GameState& currentState, Inventory& inventory);
void handleDirectionInput(GameState& currentState, Inventory& inventory);

void checkWonAndRenderResults(GameState currentState);

#endif // GAME_STATE_H
