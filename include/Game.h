#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Chips.h"

class Game {
public:
    Game();
    void play();
    void endGame();
private:
    Deck deck;
    Player player;
    Dealer dealer;
    Chips chips;
    int bet;
    bool handleBet();
    void dealInitialCards();
    void checkBlackjack();
    bool playerTurn();
    void dealerTurn();
    void determineWinner();

    void playRound();
    void endRound();
};

#endif // GAME_H