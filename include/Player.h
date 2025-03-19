#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"
#include "Deck.h"
#include "Chips.h"

class Player : public Person {
    public:
        void playTurn(Deck& deck, int& bet, Chips& chips);
        bool doubleDown(Deck& deck, int& bet, Chips& chips);
        // bool Split() const;
};

#endif // PLAYER_H