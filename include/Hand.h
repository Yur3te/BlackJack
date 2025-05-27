#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

using namespace std;

class Hand {
    public:
        Hand();
        ~Hand();
        void addCard(Card* card);
        void printHand() const;
        const vector<Card*>& getCards() const;

        int getHandValue() const;
        bool isBusted() const;
        void clearHand();
        void printCard(int index) const;
        bool canSplit() const;
        Card* removeLastCard();

        int getCardsSize() const;

    private:
        vector<Card*> cards;
};

#endif // HAND_H