#include "../include/Card.h"

#include <iostream>

using namespace std;

Card::Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

Card::~Card() {}

int Card::getValue() const {
    if (rank >= Rank::Two && rank <= Rank::Ten) return static_cast<int>(rank);
    if (rank >= Rank::Jack && rank <= Rank::King) return 10;
    return 11;
}

string Card::toString() const {
    const string suits[] = {"h", "d", "c", "s"};
    const string ranks[] = {"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    return ranks[static_cast<int>(rank)] + suits[static_cast<int>(suit)];
}

void Card::printCard() const {
    std::cout << toString() << std::endl;
}
