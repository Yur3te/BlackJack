#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include "Dealer.h"

class Game {
public:
    Game();
    void play();
private:
    Deck deck;
    Player player;
    Dealer dealer;
    int bet;
    void handleBet();
    void dealInitialCards();
    void checkBlackjack();
    void playerTurn();
    void dealerTurn();
    void determineWinner();
};

#endif // GAME_H