#include "Dealer.h"

using namespace std;

Dealer::Dealer() : Player("Dealer") {}

Card Dealer::getFirstCard() const {
    vector<Card> dealerHand = getHand();
    if (!dealerHand.empty()) {
        return dealerHand.front();
    } else {
        return Card(Ace, Spades);  // Заглушка, якщо карт нема
    }
}

int Dealer::getFirstCardScore() const {
    vector<Card> dealerHand = getHand();
    if (!dealerHand.empty()) {
        Card firstCard = dealerHand.front();
        return (firstCard.rank <= Ten) ? firstCard.rank : ((firstCard.rank < Ace) ? 10 : 11);
    }
    return 0;  //якщо карт нема
}

void Dealer::playTurn(Player& player, Deck& deck, int difficulty) {
    int target = 17;

    if (difficulty == 2) { // середній
        if (player.getScore() >= 19) target = 18;
    } else if (difficulty == 3) { // складний
        if (player.getScore() >= 18 && player.getScore() <= 21) {
            target = player.getScore(); // намагаємось наздогнати гравця
        } else {
            target = 19;
        }
    }

    while (getScore() < target) {
        receiveCard(deck.drawCard());
    }
}