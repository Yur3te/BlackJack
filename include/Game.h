#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Chips.h"

class Game {
public:
    Game();
    void play();
    void endGame();

    Card* playerHit();
    bool playerStand(); 
    bool playerDoubleDown();
    bool playerSplit();
    bool isPlayerBusted();

    void dealerPlayTurn();

    void placeBet(int bet);
    void dealInitialCards();
    int getChipsAmount() const;
    void addChips(int amount);

    QString determineOutcome();
    bool roundOver = true;
    bool isRoundOver() const;

    QString checkBlackjack();


    void endRound();

    Player& getPlayer();
    Dealer& getDealer();
private:
    Deck deck;
    Player player;
    Dealer dealer;
    Chips chips;
    int currentBet;
    bool playerTurn();
    void dealerTurn();
};

#endif // GAME_H