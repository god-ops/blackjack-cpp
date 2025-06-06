#include "Deck.h"
#include <algorithm>
#include <random>

using namespace std;

Deck::Deck() {
    for (int s = Spades; s <= Clubs; ++s) {
        for (int r = Two; r <= Ace; ++r) {
            cards.emplace_back(static_cast<Rank>(r), static_cast<Suit>(s));
        }
    }
    shuffle();  // Shuffle when created
}

void Deck::shuffle() {
    random_device rd; // генератор ранд чисел
    mt19937 g(rd()); // rd число що буде seed
    std::shuffle(cards.begin(), cards.end(), g);  // Фішер-йетс
}

Card Deck::drawCard() {
    Card c = cards.back();
    cards.pop_back();
    return c;
}