#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck {
private:
    std::vector<Card> cards;
public:
    Deck();
    void shuffle();  // Shuffle cards (Fisher-Yates algorithm)
    Card drawCard();  // Draw a card from the deck
};

#endif
