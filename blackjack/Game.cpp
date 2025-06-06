#include "Game.h"
#include <iostream>

using namespace std;

void playerTurn(Player& player, Deck& deck, int& bet, bool& exited, Player* splitHandOut) {
    while (true) {
        cout << player.getName() << "'s Turn." << endl;
        player.showHand();

        cout << "Choose action: [hit] Take card | [pass] Half bet & exit | [stand] End turn | [split] Split cards | [double] Double bet & take card" << endl;

        string choice;
        cin >> choice;

        if (choice == "hit") {
            player.receiveCard(deck.drawCard());
            player.showHand();

            if (player.getScore() > 21) {
                cout << player.getName() << " busts! You exceeded 21." << endl;
                return;
            }
        } else if (choice == "pass") {
            cout << player.getName() << " passed the round, getting back half the bet." << endl;
            player.updateBank(bet / 2);
            exited = true;
            return;
        } else if (choice == "stand") {
            cout << player.getName() << " decided to stand." << endl;
            return;
        } else if (choice == "split") {
            if (player.getHand().size() == 2 && player.getHand()[0].rank == player.getHand()[1].rank) {
                cout << player.getName() << " chooses to split the hand!" << endl;

                Player* splitHand = new Player(player.getName() + " (Split)");
                splitHand->receiveCard(player.getHand()[1]);
                player.getHand().pop_back();

                player.receiveCard(deck.drawCard());
                splitHand->receiveCard(deck.drawCard());

                cout << "First hand:" << endl;
                player.showHand();
                playerTurn(player, deck, bet, exited);

                cout << "Second hand:" << endl;
                splitHand->showHand();
                bool dummyExit = false;
                playerTurn(*splitHand, deck, bet, dummyExit);

                if (splitHandOut != nullptr) {
                    *splitHandOut = *splitHand;
                }

                delete splitHand;
                return;
            } else {
                cout << "Split not possible! You need two identical cards to split." << endl;
            }
        } else if (choice == "double") {
            if ((player.getBank() + bet) < bet * 2) {
                cout << "Not enough funds to double the bet!" << endl;
            } else {
                player.placeBet(bet);
                bet *= 2;

                cout << player.getName() << " doubled the bet to " << bet << ". Taking one final card..." << endl;
                player.receiveCard(deck.drawCard());
                player.showHand();

                if (player.getScore() > 21) {
                    cout << player.getName() << " busts after double! You exceeded 21." << endl;
                }
                return;
            }
        } else {
            cout << "Invalid choice! Try again." << endl;
        }
    }
}

void Game::saveGameResult(const Player& player, int bet, const std::string& result) {
    history.push_back({player.getName(), player.getHand(), bet, result});
    cout << "Game result saved for " << player.getName() << "." << endl;
}

void Game::showStatistics() {
    if (history.empty()) {
        cout << "\nNo game history yet. Play a round first!" << endl;
        return;
    }

    cout << "\n======= Game Statistics =======" << endl;

    int round = 1;
    for (const auto& stat : history) {
        cout << "\n Round " << round++ << endl;
        cout << " Player: " << stat.playerName << endl;
        cout << " Bet: " << stat.bet << endl;
        cout << " Result: " << stat.result << endl;
        cout << " Hand: ";
        for (const auto& card : stat.playerHand) {
            cout << card.toString() << ", ";
        }
        cout << "\n-------------------------------";
    }

    cout << "\n================================\n";
}

void Game::start(int mode) {
    string playerName, secondPlayerName;
    cout << "Enter your name: ";
    cin >> playerName;

    Player player(playerName);
    Dealer dealer;
    Deck deck;

    Player secondPlayer("");
    if (mode == 1) {
        cout << "Enter your friend's name: ";
        cin >> secondPlayerName;
        secondPlayer = Player(secondPlayerName);
    }

    int difficulty;
    cout << "Choose difficulty level:\n1. Easy\n2. Medium\n3. Hard\n";
    cin >> difficulty;

    bool continuePlaying = true;
    while (continuePlaying) {
        system("cls");
        deck.shuffle();
        player.resetHand();
        dealer.resetHand();
        if (mode == 1) secondPlayer.resetHand();

        cout << "==========================\n Blackjack Game\n==========================\n";
        cout << "Player: " << player.getName() << "\nBank: " << player.getBank() << " Coins\n--------------------------\n";

        int bet1 = 0, bet2 = 0;
        do {
            cout << player.getName() << ", enter your bet (bank: " << player.getBank() << "): ";
            cin >> bet1;
        } while (bet1 > player.getBank() || bet1 <= 0);
        player.placeBet(bet1);

        if (mode == 1) {
            do {
                cout << secondPlayer.getName() << ", enter your bet (bank: " << secondPlayer.getBank() << "): ";
                cin >> bet2;
            } while (bet2 > secondPlayer.getBank() || bet2 <= 0);
            secondPlayer.placeBet(bet2);
        }

        player.receiveCard(deck.drawCard());
        player.receiveCard(deck.drawCard());
        dealer.receiveCard(deck.drawCard());
        dealer.receiveCard(deck.drawCard());

        if (mode == 1) {
            secondPlayer.receiveCard(deck.drawCard());
            secondPlayer.receiveCard(deck.drawCard());
        }

        cout << "--------------------------\nDealer's First Card: " << dealer.getFirstCard().toString() << "\n--------------------------\n";

        bool exited1 = false, exited2 = false;
        Player playerSplit("");
        playerTurn(player, deck, bet1, exited1, &playerSplit);

        Player secondSplit("");
        if (mode == 1)
            playerTurn(secondPlayer, deck, bet2, exited2, &secondSplit);

        if (!exited1 && player.getScore() <= 21)
            dealer.playTurn(player, deck, difficulty);
        if (mode == 1 && !exited2 && secondPlayer.getScore() <= 21)
            dealer.playTurn(secondPlayer, deck, difficulty);

        dealer.showHand();

        auto resolveResult = [&](Player& p, int bet) {
            if (p.getScore() > 21) return string("Lost");
            if (dealer.getScore() > 21) return string("Won");
            if (p.getScore() > dealer.getScore()) return string("Won");
            if (p.getScore() == dealer.getScore()) return string("Tie");
            return string("Dealer wins");
        };

        if (exited1) {
            saveGameResult(player, bet1, "Lost");
        } else {
            string result = resolveResult(player, bet1);
            cout << player.getName() << " " << result << ".\n";
            if (result == "Won") {
                double multiplier = (player.getScore() == 21 && player.getHand().size() == 2) ? 2.5 : 2.0;
                player.updateBank(static_cast<int>(bet1 * multiplier));
            } else if (result == "Tie") {
                player.updateBank(bet1); // возвращаем ставку
            }
            saveGameResult(player, bet1, result);
        }

        if (!playerSplit.getHand().empty()) {
            string splitResult = resolveResult(playerSplit, bet1);
            cout << playerSplit.getName() << " " << splitResult << ".\n";
            if (splitResult == "Won") {
                double multiplier = (playerSplit.getScore() == 21 && playerSplit.getHand().size() == 2) ? 2.5 : 2.0;
                player.updateBank(static_cast<int>(bet1 * multiplier));
            } else if (splitResult == "Tie") {
                player.updateBank(bet1);
            }
            saveGameResult(playerSplit, bet1, splitResult);
        }

        if (mode == 1) {
            if (exited2) {
                saveGameResult(secondPlayer, bet2, "Lost");
            } else {
                string result2 = resolveResult(secondPlayer, bet2);
                cout << secondPlayer.getName() << " " << result2 << ".\n";
                if (result2 == "Won") {
                    double multiplier = (secondPlayer.getScore() == 21 && secondPlayer.getHand().size() == 2) ? 2.5 : 2.0;
                    secondPlayer.updateBank(static_cast<int>(bet2 * multiplier));
                } else if (result2 == "Tie") {
                    secondPlayer.updateBank(bet2);
                }
                saveGameResult(secondPlayer, bet2, result2);
            }
        }

        cout << "\nDo you want to play again? (1 - Yes / 0 - No): ";
        int choice;
        cin >> choice;
        continuePlaying = (choice == 1);
    }
}
