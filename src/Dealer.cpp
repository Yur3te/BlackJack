#include "../include/Dealer.h"

#include <iostream>


void Dealer::playTurn(Deck& deck) {
    cout << "Dealer's hand: " << endl;
    printHand();
    cout << "Hand value: " << getHandValue() << endl;
    while (getHandValue() < 17) {
        Card* newCard = deck.deal();
        addCard(newCard);
        cout << "Dealer drew: ";
        newCard->printCard();
        cout << "Hand value: " << getHandValue() << endl;
    }
    if (isBusted()) {
        cout << "Dealer busted!" << endl;
    }
}

void Dealer::printFirstCard() const {
    cout << "Dealer's first card is: " << endl;
    hand[0]->printCard();
}