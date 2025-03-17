#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

enum class Suit { Hearts, Diamonds, Clubs, Spades };
enum class Rank {Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King,};

class Card {
    public:
        Card();
        ~Card();
        Card(Rank rank, Suit suit);
        int getValue() const;
        void printCard();
        string toString() const;
    private:
        Rank rank;
        Suit suit;
};

#endif // CARD_H