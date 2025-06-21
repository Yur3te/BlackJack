#include "../include/Game.h"

#include <iostream>
#include <limits>

using namespace std;

Game::Game() {
    deck.shuffle();
    currentBet = 0;
    chips.loadChips();
}
    
void Game::endRound() {
    // chips.saveChips();
    // chips.printChips();
    deck.reset();
    deck.shuffle();
    player.clearHand();
    dealer.clearHand();
}


void Game::dealInitialCards() {
    player.addCard(deck.deal());
    dealer.addCard(deck.deal());
    player.addCard(deck.deal());
    dealer.addCard(deck.deal());
}

QString Game::checkBlackjack() {
    bool playerBJ = player.getHandValue() == 21 && player.getFirstHand().getCards().size() == 2;
    bool dealerBJ = dealer.getHandValue() == 21 && dealer.getFirstHand().getCards().size() == 2;

    if (playerBJ || dealerBJ) {
        roundOver = true;

        if (playerBJ && dealerBJ) {
            return "RPush! Both you and the dealer have Blackjack.";
        } else if (playerBJ) {
            int winnings = static_cast<int>(currentBet * 1.5);
            chips.addChips(winnings + currentBet);  // zwrot zakładu + wygrana
            return QString("Blackjack! You won %1 chips!").arg(winnings);
        } else {
            return "Dealer has Blackjack!";
        }
    }

    return "";
}


// bool Game::playerTurn() {
//     int i = 0;
//     while (i < player.hands.size()) { 
//         player.currentHandIndex = i;

//         if(player.hands.size() > 1){
//             cout << "Hand #" << (i + 1) << ":" << endl;
//             player.getCurrentHand().printHand();
//             cout << "Hand value: " << player.getCurrentHand().getHandValue() << endl;
//         }
//         player.playTurn(deck, currentBet, chips); 

//         cout << "Final state of Hand #" << (i + 1) << ":" << endl;
//         player.getCurrentHand().printHand();
//         cout << "Hand value: " << player.getCurrentHand().getHandValue() << endl;

//         if (player.getCurrentHand().isBusted()) {
//             cout << "Hand #" << (i + 1) << " busted!" << endl;
//         }

//         i++; 
//     }
//     return true;
// }

void Game::dealerTurn() {
    dealer.playTurn(deck);
}

void Game::determineWinner() {
    int dealerScore = dealer.getHandValue();

    for (int i = 0; i < player.hands.size(); i++) {
        int playerScore = player.hands[i].getHandValue();
        cout << "Result for Hand #" << (i + 1) << ":" << endl;
        if (playerScore > 21) {
            // chips.removeChips(currentBet);
        } else if (dealerScore > 21 || playerScore > dealerScore) {
            cout << "You win! You won " << currentBet*2 << " chips." << endl;
            chips.addChips(currentBet*2);
        } else if (playerScore == dealerScore) {
            cout << "Push!" << endl;
            chips.addChips(currentBet);
        } else {
            cout << "Dealer wins! You lost " << currentBet << " chips." << endl;
        }
    }
}

QString Game::determineOutcome() {
    const Hand& playerHand = player.getFirstHand();
    const Hand& dealerHand = dealer.getFirstHand();

    int playerValue = playerHand.getHandValue();
    int dealerValue = dealerHand.getHandValue();

    QString outcome;

    if (playerHand.isBusted()) {
        outcome = "You lost! Your hand is busted.";
    } else if (dealerHand.isBusted()) {
        outcome = "You won! Dealer's hand is busted.";
        chips.addChips(currentBet * 2);
    } else if (playerValue > dealerValue) {
        outcome = "You won!";
        chips.addChips(currentBet * 2);
    } else if (playerValue < dealerValue) {
        outcome = "You lost!";
    } else {
        outcome = "Push, you tied with the dealer.";
        chips.addChips(currentBet);
    }

    roundOver = true;
    
    chips.saveChips();
    currentBet = 0;
    return outcome;
}


bool Game::isRoundOver() const {
    return roundOver;
}


Player& Game::getPlayer() {
    return player;
}

Dealer& Game::getDealer() {
    return dealer;
}

Card* Game::playerHit() {
    return player.hit(deck);
}

bool Game::playerStand() {
    return player.stand();
}

bool Game::playerDoubleDown() {
    return player.doubleDown(deck, currentBet, chips);
}
bool Game::playerSplit() {
    return player.split(deck, currentBet, chips);
}

bool Game::isPlayerBusted() {
    return player.isBusted();
}

void Game::dealerPlayTurn() {
    dealer.playTurn(deck);
}

void Game::placeBet(int bet) {
    currentBet = bet;
    chips.removeChips(currentBet);
    chips.saveChips();
}

int Game::getChipsAmount() const {
    return chips.getChips();
}