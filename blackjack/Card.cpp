#include "Card.h"

using namespace std;

Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

string Card::toString() const {
    string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
    string suits[] = { "Spades", "Hearts", "Diamonds", "Clubs" };
    return ranks[rank - 2] + " " + suits[suit];
}