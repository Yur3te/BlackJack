#include <iostream>
#include "include/Game.h"

#include "include/Deck.h"

using namespace std;

int main() {

    Deck deck;
    cout << "-----SHUFFLED DECK-----" << endl;
    deck.shuffle();
    deck.printDeck();
    cout << "-----DEALING EXAMPLE HOLDEM HAND-----" << endl;
    for (int i = 0; i < 2; i++) {
        deck.deal()->printCard();
    }
    return 0;
}