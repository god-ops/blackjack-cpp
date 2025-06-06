#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

enum Suit { Spades, Hearts, Diamonds, Clubs };  // ♠ ♥ ♦ ♣
enum Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

struct Card {
    Rank rank;
    Suit suit;

    Card(Rank r, Suit s);
    string toString() const;  // Convert card to string
};

#endif