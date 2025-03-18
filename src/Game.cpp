#include "../include/Game.h"

#include <iostream>

using namespace std;

Game::Game() {
    deck.shuffle();
    bet = 0;
}
    
void Game::play() {
    bool keepPlaying = true;
    while(keepPlaying) {
        playRound();
        endRound();
        cout << "Do you want to play another round? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'n') {
            keepPlaying = false;
        }
    }

    cout << "Thanks for playing!" << endl;
}

void Game::playRound() {
    cout << "Welcome to Blackjack!" << endl;
    chips.loadChips();
    chips.printChips();
    while (!handleBet()) {
        cout << "Please enter a valid bet!" << endl;
    }
    dealInitialCards();
    checkBlackjack();
    if (!playerTurn()) {
        determineWinner();
        return;
    }
    dealerTurn();
    determineWinner();
}

void Game::endRound() {
    chips.saveChips();
    chips.printChips();
    deck.reset();
    deck.shuffle();
    player.clearHand();
    dealer.clearHand();
    cout << "-----------------------------------" << endl;
}

bool Game::handleBet() {
    cout << "Enter your bet: ";
    cin >> bet;
    if (bet <= 0) {
        cout << "Bet must be greater than 0!" << endl;
        return false;
    }

    if (bet > chips.getChips()) {
        cout << "Not enough chips! You only have " << chips.getChips() << " chips." << endl;
        return false;
    }

    return true;

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
            bet = static_cast<int>(bet * 1.5);
        } else {
            cout << "Dealer has blackjack! You lose!" << endl;
        }
    }
}

bool Game::playerTurn() {
    player.playTurn(deck);
    if (player.getHandValue() > 21) {
        cout << "You busted! You lose!" << endl;
        chips.removeChips(bet);
        return false;
    }
    return true;
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
        chips.removeChips(bet);
    } else if (dealerScore > 21 || playerScore > dealerScore) {
        cout << "You win!" << endl;
        chips.addChips(bet);
    } else if (playerScore == dealerScore) {
        cout << "Push!" << endl;
    } else {
        cout << "Dealer wins!" << endl;
        chips.removeChips(bet);
    }
}