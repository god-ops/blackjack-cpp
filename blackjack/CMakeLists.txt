cmake_minimum_required(VERSION 3.30)
project(blackjack)

set(CMAKE_CXX_STANDARD 20)

add_executable(blackjack
        main.cpp
        Game.cpp
        Player.cpp
        Dealer.cpp
        Deck.cpp
        Card.cpp
)
