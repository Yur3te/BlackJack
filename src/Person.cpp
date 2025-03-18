#include "../include/Person.h"

#include <iostream>


Person::Person() {}

void Person::addCard(Card* card) {
    hand.push_back(card);
}

void Person::printHand() const {
    for (Card* card : hand) {
        card->printCard();
    }
}

int Person::getHandValue() const {
    int sum = 0;
    int numAces = 0;
    for (Card* card : hand) {
        sum += card->getValue();
        if (card->getValue() == 11) {
            numAces++;
        }
    }
    while (sum > 21 && numAces > 0) {
        sum -= 10;
        numAces--;
    }
    return sum;
}

bool Person::isBusted() const {
    return getHandValue() > 21;
}

Person::~Person() {
    for (Card* card : hand) {
        delete card;
    }
}