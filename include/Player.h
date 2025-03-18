#ifndef PLAYER_H
#define PLAYER_H

#include "person.h"
#include "Deck.h"

class Player : public Person {
    public:
        void playTurn(Deck& deck);
};

#endif // PLAYER_H