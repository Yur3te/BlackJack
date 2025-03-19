#include "../include/Player.h"

#include <iostream>

#include "../include/Chips.h"

void Player::playTurn(Deck& deck, int& bet, Chips& chips) {
    while (true) {
        char choice;
        cout << "Do you want to hit, stand or double? (h/s/d): ";
        cin >> choice;
        if (choice == 'h') {
            Card* newCard = deck.deal();
            addCard(newCard);
            cout << "You drew: ";
            newCard->printCard();
            cout << "New hand value: " << getHandValue() << endl;
            if (isBusted()) {
                cout << "You busted!" << endl;
                break;
            }
        } else if (choice == 's'){
            cout << "You chose to stand!" << endl;
            break;
        } else if (choice == 'd') {
            doubleDown(deck, bet, chips);
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
}

bool Player::doubleDown(Deck& deck, int& bet, Chips& chips) {
    if (bet * 2 > chips.getChips()) {
        cout << "Not enough chips to double down!" << endl;
        return false;
    }
    
    chips.removeChips(bet); // Deduct the extra bet amount
    bet *= 2; // Double the bet

    cout << "You chose to double down! You receive one final card." << endl;
    Card* newCard = deck.deal();
    addCard(newCard);
    cout << "You drew: ";
    newCard->printCard();
    cout << "New hand value: " << getHandValue() << endl;
    
    return true;
}

