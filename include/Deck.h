#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "Card.h"
#include <vector>

using namespace std;

class Deck {
    public:
        Deck();
        ~Deck();
        void printDeck();
        void shuffle();
        void deal();
    private:
        vector<Card*> deck;
};

#endif // DECK_H