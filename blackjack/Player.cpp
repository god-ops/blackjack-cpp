#include "Player.h"
#include "Card.h"
#include <iostream>
#include <fstream>

using namespace std;

Player::Player(const string& name, bool loadData) : name(name), bank(1000) {
    if (loadData) loadPlayerData();  //Завантажуємо банк тільки якщо це не новий гравець
}

string Player::getName() const {
    return name;
}

void Player::receiveCard(Card card) {
    hand.push_back(card);
}

int Player::getScore() const {
    int score = 0;
    int aceCount = 0;

    for (const auto& card : hand) {
        if (card.rank <= Ten) {
            score += card.rank;
        } else if (card.rank < Ace) {
            score += 10;
        } else {
            aceCount++;
            score += 11;
        }
    }

    while (score > 21 && aceCount > 0) {
        score -= 10;
        aceCount--;
    }

    return score;
}

void Player::showHand() const {
    cout << name << " has cards: ";
    for (const auto& card : hand) {
        cout << card.toString() << ", ";
    }
    cout << " | Score: " << getScore() << endl;
}

std::vector<Card> Player::getHand() const {
    return hand;
}

void Player::placeBet(int amount) {
    if (amount <= 0) {
        cout << "Invalid bet amount! You must bet more than 0.\n";
        return;
    }

    if (amount > bank) {
        cout << "Not enough funds! Your bank: " << bank << endl;
    } else {
        bank -= amount;
        cout << name << " placed a bet of " << amount << " coins. Remaining bank: " << bank << endl;
    }
}

void Player::updateBank(int amount) {
    bank += amount;
    cout << name << "'s updated bank: " << bank << " coins.\n";
    savePlayerData();
}

int Player::getBank() const {
    return bank;
}

void Player::resetHand() {
    hand.clear();
}

void Player::savePlayerData() {
    ifstream file_in("players.txt");
    vector<pair<string, int>> players;
    string storedName;
    int storedBank;

    while (file_in >> storedName >> storedBank) {
        if (storedName == name) {
            storedBank = bank;
        }
        players.push_back({storedName, storedBank});
    }
    file_in.close();

    ofstream file_out("players.txt", ios::trunc);
    for (const auto& p : players) {
        file_out << p.first << " " << p.second << endl;
    }
    file_out.close();
}

void Player::loadPlayerData() {
    ifstream file("players.txt");
    if (!file.is_open()) return;

    string storedName;
    int storedBank;

    while (file >> storedName >> storedBank) {
        if (storedName == name) {
            bank = storedBank;
            break;
        }
    }

    file.close();
}
