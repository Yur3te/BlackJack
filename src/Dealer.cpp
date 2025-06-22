#include "../include/Dealer.h"

#include <iostream>


void Dealer::playTurn(Deck& deck) {
    while (getHandValue() < 17) {
        Card* newCard = deck.deal();
        addCard(newCard);
    }

}