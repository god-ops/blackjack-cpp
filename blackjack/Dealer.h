#ifndef DEALER_H
#define DEALER_H

#include "Player.h"
#include "Deck.h"

class Dealer : public Player {
public:
    Dealer();
    Card getFirstCard() const;
    int getFirstCardScore() const;
    void playTurn(Player& player, Deck& deck, int difficulty);
};

#endif
