#include "story.h"
#include <iostream>
using std::cout;
using std::cin;
using std::string;
void displayIntro() {
    cout << "\n\n********** WELCOME TO ARKADIA **********\n\n";
    cout << "Your adventure begins... Explore the land and uncover its secrets.\n";
    cout << "Good luck, adventurer!\n\n";
}

void puzzleChallenge() {
    string answer;
    cout << "\nA mysterious voice asks: 'I speak without a mouth and hear without ears. I have no body, but I come alive with wind. What am I?'\n";
    cout << "Enter your answer: ";
    cin >> answer;

    if (answer == "echo" || answer == "Echo") {
        cout << "Correct! The path forward opens.\n";
    } else {
        cout << "Incorrect! The cave remains blocked.\n";
        // Force return to Forest if the puzzle is failed.
        cout << "You retreat to the Forest in defeat.\n";
    }
}

