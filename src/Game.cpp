#include "../include/Game.h"

#include <iostream>

using namespace std;

Game::Game() {
    deck.shuffle();
    bet = 0;
}

void Game::play() {
    handleBet();
    dealInitialCards();
    checkBlackjack();
    playerTurn();
    dealerTurn();
    determineWinner();
}

void Game::handleBet() {
    cout << "Enter your bet: ";
    cin >> bet;
}

void Game::dealInitialCards() {
    player.addCard(deck.deal());
    dealer.addCard(deck.deal());
    player.addCard(deck.deal());
    dealer.addCard(deck.deal());

    dealer.printFirstCard();
    cout << "Your hand: " << endl;
    player.printHand();
    cout<<"Hand value: " <<player.getHandValue()<<endl;
}

void Game::checkBlackjack() {
    if (player.getHandValue() == 21 || dealer.getHandValue() == 21) {
        if (player.getHandValue() == 21 && dealer.getHandValue() == 21) {
            cout << "Push! Both have blackjack!" << endl;
        } else if (player.getHandValue() == 21) {
            cout << "Blackjack! You win 1.5x your bet!" << endl;
        } else {
            cout << "Dealer has blackjack! You lose!" << endl;
        }
        exit(0);
    }
}

void Game::playerTurn() {
    player.playTurn(deck);
}

void Game::dealerTurn() {
    dealer.playTurn(deck);
}

void Game::determineWinner() {
    int playerScore = player.getHandValue();
    int dealerScore = dealer.getHandValue();

    cout << "Dealer's hand: " << endl;
    dealer.printHand();
    cout << "Dealer score: " << dealerScore << endl;

    if (playerScore > 21) {
        cout << "You busted! You lose!" << endl;
    } else if (dealerScore > 21 || playerScore > dealerScore) {
        cout << "You win!" << endl;
    } else if (playerScore == dealerScore) {
        cout << "Push!" << endl;
    } else {
        cout << "Dealer wins!" << endl;
    }
}