#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
#include <vector>
#include <string>
#include <iostream>

struct GameStats {
    std::string playerName;
    std::vector<Card> playerHand;
    int bet;
    std::string result;
};

class Game {
private:
    std::vector<GameStats> history;

public:
    void start(int mode);
    void saveGameResult(const Player& player, int bet, const std::string& result);
    void showStatistics();
};

void playerTurn(Player& player, Deck& deck, int& bet, bool& exited, Player* splitHandOut = nullptr);

#endif
