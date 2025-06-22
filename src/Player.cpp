#include "../include/Player.h"

#include <iostream>

#include "../include/Chips.h"


bool Player::doubleDown(Deck& deck, int& bet, Chips& chips) {
    if (bet > chips.getChips()) {
        return false;
    }
    
    chips.removeChips(bet);
    bet *= 2;
    Card* newCard = deck.deal();
    addCard(newCard);
    return true;
}

Card* Player::hit(Deck& deck) {
    Card* card = deck.deal();  
    addCard(card);             
    return card;               
}

bool Player::stand() {
    return true;
}


bool Player::split(Deck& deck, int& bet, Chips& chips) {
    if(!getCurrentHand().canSplit()) {
        return false;
    }
    if(bet > chips.getChips()){
        return false;
    }
    chips.removeChips(bet);


    Hand newHand;
    
    Card* movedCard = hands[currentHandIndex].removeLastCard();
    newHand.addCard(movedCard);

    hands[currentHandIndex].addCard(deck.deal());
    newHand.addCard(deck.deal());

    hands.push_back(newHand);

    return true;
}

Hand& Player::getCurrentHand() {
    return hands[currentHandIndex];
}
