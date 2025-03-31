#include "../include/Hand.h"


#include <iostream>

using namespace std;

Hand::Hand() {}

Hand::~Hand() {}

void Hand::addCard(Card* card) {
    cards.push_back(card);
}


void Hand::printHand() const {
    for (Card* card : cards) {
        card->printCard();
    }
}

int Hand::getHandValue() const {
    int sum = 0;
    int numAces = 0;
    for (Card* card : cards) {
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

bool Hand::isBusted() const {
    return getHandValue() > 21;
}

void Hand::printCard(int index) const {
        if (index >= 0 && index < cards.size()) {
            cards[index]->printCard();
        }
    }

bool Hand::canSplit() const{
        return (cards.size() == 2 &&cards[0]->getValue() == cards[1]->getValue());
    }


void Hand::clearHand() {
    for (Card* card : cards) {
        delete card;
    }
    cards.clear();
}

Card* Hand::removeLastCard() {
    if (!cards.empty()) {
        Card* lastCard = cards.back();
        cards.pop_back();
        return lastCard;
    }
    return nullptr;
}


int Hand::getCardsSize() const {
    return cards.size();
}