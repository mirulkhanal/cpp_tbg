#include "game_state.h"
#include "inventory.h"
#include "story.h"
#include "ui.h"
#include <iostream>
#include <map>

using namespace std;

struct NPC {
    string name;
    string description;
    vector<string> dialogueOptions;
    string requiredItem; // Item needed to trigger special interactions.
    string reward;       // Reward for completing their quest.

    NPC(string n, string d, vector<string> options, string item, string rew)
        : name(n), description(d), dialogueOptions(options), requiredItem(item), reward(rew) {}

    void interact(Inventory& inventory) {
        cout << name << ": " << description << "\n";
        for (size_t i = 0; i < dialogueOptions.size(); ++i) {
            cout << i + 1 << ". " << dialogueOptions[i] << "\n";
        }
        cout << "\nChoose an option (or 0 to exit): ";
        int choice;
        cin >> choice;

        if (choice == 0) return;

        if (choice > 0 && choice <= dialogueOptions.size()) {
            cout << "You: " << dialogueOptions[choice - 1] << "\n";

            if (requiredItem.empty() || inventory.hasItem(requiredItem)) {
                cout << name << ": Thank you! Here is your reward: " << reward << ".\n";
                if (!reward.empty()) {
                    inventory.addItem({reward, "Rewarded by " + name});
                }
            } else {
                cout << name << ": You don't have the required item (" << requiredItem << ")!\n";
            }
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
};

StateMap stateTransitions = {
    {GameState::START, {{'L', GameState::FOREST}, {'R', GameState::VILLAGE}}},
    {GameState::FOREST, {{'L', GameState::CAVE}, {'R', GameState::START}}},
    {GameState::CAVE, {{'L', GameState::MOUNTAIN}, {'R', GameState::FOREST}}},
    {GameState::VILLAGE, {{'L', GameState::LAKE}, {'R', GameState::START}}},
    {GameState::LAKE, {{'L', GameState::MOUNTAIN}, {'R', GameState::VILLAGE}}},
    {GameState::MOUNTAIN, {{'L', GameState::CAVE}, {'R', GameState::LAKE}}}
};

vector<NPC> npcList = {
    NPC("Elder of the Village",
        "A wise elder who knows secrets of the land.",
        {"Tell me about the cave.", "Do you have any tasks for me?"},
        "Glowing Fruit",
        "Key to the Cave"),
    NPC("Lake Spirit",
        "A mystical being guarding the lake's secrets.",
        {"Reveal the secrets of the lake."},
        "Map",
        "Path to Hidden Treasure")
};

void handleGameState(GameState& currentState, Inventory& inventory) {
    switch (currentState) {
        case GameState::START:
            displayIntro();
            cout << "You stand at a crossroads under a starlit sky.\n";
            cout << "Where will you go first?\n";
            cout << "L -> Forest, R -> Village\n";
            break;
        case GameState::FOREST:
            cout << "You wander into a dense, ancient forest. You hear the rustling of leaves.\n";
            cout << "Among the trees, you find an odd glowing fruit.\n";
            inventory.addItem({"Glowing Fruit", "An enchanted fruit from the forest depths"});
            cout << "L -> Explore deeper, R -> Return to Start\n";
            break;
        case GameState::CAVE:
            cout << "You stumble into a cold, dark cave. The air is thick with mystery.\n";
            cout << "An inscription on the wall reads: 'Only the enlightened shall pass.'\n";
            puzzleChallenge();
            cout << "L -> Venture further into darkness, R -> Exit to Forest\n";
            break;
        case GameState::VILLAGE:
            cout << "You arrive at a lively village. Merchants offer goods, and villagers share tales.\n";
            cout << "A friendly merchant offers a trade: 'Bring me a glowing fruit, and I'll give you a map.'\n";
            if (inventory.hasItem("Glowing Fruit")) {
                inventory.useItem("Glowing Fruit");
                inventory.addItem({"Map", "A map showing paths to hidden treasures"});
                cout << "You trade the glowing fruit for a map.\n";
            } else {
                cout << "You don't have a glowing fruit to trade.\n";
            }
            cout << "L -> Talk to the Elder, R -> Head to the Lake\n";
            break;
        case GameState::LAKE:
            cout << "You stand at a serene lake. The water sparkles with a magical glow.\n";
            cout << "A voice echoes: 'Cast an item into the water to uncover its secret.'\n";

            if (inventory.hasItem("Map")) {
                cout << "The map reveals a hidden path to the mountain!\n";
                // Reward the player for bringing the map.
            } else {
                cout << "Without guidance, the lake remains mysterious.\n";
            }
            cout << "L -> Swim, R -> Head to the Mountain\n";
            break;

        case GameState::MOUNTAIN:
            cout << "You climb a steep mountain. The peak is shrouded in mist, hiding a treasure.\n";
            cout << "L -> Search for treasure, R -> Descend to Start\n";
            inventory.addItem({"Golden Amulet", "A mystical amulet that grants victory"});
            break;
        case GameState::END:
            checkWonAndRenderResults(currentState);
            break;
        case GameState::WIN:
            cout << "You uncover the mysteries of Arkadia and emerge victorious!\n";
            break;
    }
    handleDirectionInput(currentState, inventory);
}


void handleDirectionInput(GameState& currentState, Inventory& inventory) {
    char direction;
    cout << "Enter direction (L/R), I to check inventory, or U to use an item: ";
    cin >> direction;

    if (direction == 'I' || direction == 'i') {
        showInventoryMenu(inventory);
    } else if (direction == 'U' || direction == 'u') {
        std::string itemName;
        cout << "Enter the name of the item to use: ";
        cin.ignore();
        std::getline(cin, itemName);

        if (inventory.useItem(itemName)) {
            if (itemName == "Golden Amulet") {
                cout << "The amulet unlocks a hidden door to the WIN state!\n";
                currentState = GameState::WIN;
            }
        }
    } else {
        // Existing logic for directions.
        auto it = stateTransitions.find(currentState);
        if (it != stateTransitions.end()) {
            auto transitionState = it->second.find(direction);
            if (transitionState != it->second.end()) {
                currentState = transitionState->second;
            } else {
                cout << "\nInvalid direction! Please try again.\n";
            }
        } else {
            cout << "\nInvalid state! Please try again.\n";
        }
    }
}


void checkWonAndRenderResults(GameState currentState) {
    if (currentState == GameState::END) {
        cout << "\nYour journey ends here. Congratulations on your adventure!\n";
    }
}
