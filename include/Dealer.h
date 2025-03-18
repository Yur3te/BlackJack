#ifndef DEALER_H
#define DEALER_H

#include "person.h"
#include "Deck.h"

class Dealer : public Person {
    public:
        void playTurn(Deck& deck);
        void printFirstCard() const;
};

#endif // DEALER_H