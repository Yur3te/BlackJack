#include "../include/Player.h"

#include <iostream>

#include "../include/Chips.h"


bool Player::doubleDown(Deck& deck, int& bet, Chips& chips) {
    if (bet > chips.getChips()) {
        return false;
    }
    
    chips.removeChips(bet); // Deduct the extra bet amount
    bet *= 2; // Double the bet
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

// bool Player::stand() {
//     return true;
// }



bool Player::split(Deck& deck, int& bet, Chips& chips) {
    if(!getCurrentHand().canSplit()) {
        cout << "You can't split this hand silly, you need two cards with the same value ;>" << endl;
        return false;
    }
    if(bet *2 > chips.getChips()){
        cout << "Not enough chips to split!" << endl;
        return false;
    }
    cout<<"You chose to split!"<<endl;
    chips.removeChips(bet);


    Hand newHand;
    
    Card* movedCard = hands[currentHandIndex].removeLastCard();
    newHand.addCard(movedCard);

    hands[currentHandIndex].addCard(deck.deal());
    newHand.addCard(deck.deal());

    
    cout << "Adding new hand..." << endl;
    hands.push_back(newHand);


    printHand();
    cout << "Hand value: " << getHandValue() << endl;

    return true;
}

Hand& Player::getCurrentHand() {
    return hands[currentHandIndex];
}
