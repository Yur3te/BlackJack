#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include "Card.h"
#include "Hand.h"

class Person {
    public:
        
        int currentHandIndex = 0;
        
        Person();
        virtual ~Person();
        void addCard(Card* card);
        void printHand() const;
        int getHandValue() const;
        bool isBusted() const;
        void clearHand();
        
        const Hand& getFirstHand() const;
        vector<Hand> hands;
        // TODO: Refactor hands to be private and add proper access methods
    // private:
    //     vector<Hand> hands;
};



#endif // PERSON_H