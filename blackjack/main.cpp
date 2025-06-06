#include <iostream>
#include <locale>
#include "Game.h"

using namespace std;

void showMenu() {
    cout << "==============================\n";
    cout << "     Welcome to Blackjack\n";
    cout << "==============================\n";
    cout << "1. Play with a friend\n";
    cout << "2. Play against the dealer\n";
    cout << "3. Rules\n";
    cout << "4. Show statistics\n";
    cout << "0. Exit\n";
    cout << "==============================\n";
    cout << "Choose mode: ";
}

void showRules() {
    cout << "\nRULES\n";
    cout << "1. The game is played by 1 or 2 players.\n";
    cout << "2. The goal is to score 21 points or get as close as possible.\n";
    cout << "3. The player can take more cards or stop.\n";
    cout << "4. The dealer takes cards until they have at least 17 points.\n";
    cout << "5. If the points exceed 21, it's a loss.\n";
    cout << "6. If the players are closer to 21 than the dealer, they win!\n";
}

int main() {
    setlocale(LC_CTYPE, ".UTF8");

    Game game;
    int mode;

    do {
        showMenu();
        cin >> mode;

        switch (mode) {
            case 1:
            case 2:
                game.start(mode);
            break;
            case 3:
                showRules();
            break;
            case 4:
                game.showStatistics();
            break;
            case 0:
                cout << "THANK YOU for playing!\n";
            break;
            default:
                cout << "Incorrect choice\n";
        }

    } while (mode != 0);

    return 0;
}
