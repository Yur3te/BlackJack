#include "../include/Player.h"

#include <iostream>

#include "../include/Chips.h"

void Player::playTurn(Deck& deck, int& bet, Chips& chips) {
    while (true) {
        char choice;
        cout << "Do you want to hit, stand, double or split?? (h/s/d/p): ";
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
        } else if (choice == 'p') {
            if (!split(deck, bet, chips)) { 
                continue;
            }
            break;  
        } else if (choice == 'l') {
            cout << "Current hand: " << endl;
            printHand();
        }
        else {
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
