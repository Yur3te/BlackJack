#include "../include/Player.h"

#include <iostream>

void Player::playTurn(Deck& deck) {
    char choice;
    while (true) {
        cout << "Do you want to hit or stand? (h/s): ";
        cin >> choice;
        if (choice == 'h') {
            addCard(deck.deal());
            cout << "Your hand: " << endl;
            printHand();
            cout << "Hand value: " << getHandValue() << endl;
            if (isBusted()) {
                cout << "You busted!" << endl;
                break;
            }
        } else if (choice == 's') {
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
}