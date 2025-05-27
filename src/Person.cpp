#include "../include/Person.h"

#include <iostream>


Person::Person() {
    hands.emplace_back();
}

void Person::addCard(Card* card) {
    if (hands.empty()) {
        hands.emplace_back();
    }
    hands[currentHandIndex].addCard(card);
}

void Person::printHand() const {
    hands[currentHandIndex].printHand();
}

int Person::getHandValue() const {
    return hands[currentHandIndex].getHandValue();
}

bool Person::isBusted() const {
    return hands[currentHandIndex].isBusted();
}

void Person::clearHand() {
    for (auto& hand : hands) {
        hand.clearHand();
    }
    hands.clear();
    hands.emplace_back();
    currentHandIndex = 0;
}


const std::vector<Hand>& Person::getHands() const {
    return hands;
}


const Hand& Person::getFirstHand() const {
    return hands[0];
}


Person::~Person() {
    for (Hand& hand : hands) {
        hand.clearHand();
    }
}
