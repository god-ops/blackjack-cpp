#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.h"

class Player {
private:
    std::string name;
    std::vector<Card> hand;
    int bank;
public:
    Player(const std::string& name, bool loadData = true);
    void receiveCard(Card card);
    int getScore() const;
    void showHand() const;
    std::string getName() const;
    std::vector<Card> getHand() const;
    void placeBet(int amount);
    int getBank() const;
    void updateBank(int amount);
    void resetHand();
    void savePlayerData();
    void loadPlayerData();
};

#endif
