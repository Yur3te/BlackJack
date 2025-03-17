#include "../include/Deck.h"

#include <algorithm>
#include <random> 


Deck::Deck() {
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            deck.push_back(new Card(static_cast<Rank>(j), static_cast<Suit>(i)));
        }
    }
}

Deck::~Deck() {
    for (Card* card : deck) {
        delete card;
    }
}

void Deck::shuffle() {
    random_device rd;
    mt19937 g(rd());

    std::shuffle(deck.begin(), deck.end(), g); 
}

Card* Deck::deal() {
    if (deck.empty()) {
        cout << "Deck is empty!" << endl;
        return nullptr;
    }
    Card* card = deck.back();
    deck.pop_back();
    return card;
}

void Deck::printDeck() {
    for (Card* card : deck) {
        card->printCard();
    }
}