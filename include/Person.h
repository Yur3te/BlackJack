#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include "Card.h"

class Person {
    public:
        Person();
        virtual ~Person();
        void addCard(Card* card);
        void printHand() const;
        int getHandValue() const;
        bool isBusted() const;
        void clearHand();
    protected:
        vector<Card*> hand;
};



#endif // PERSON_H