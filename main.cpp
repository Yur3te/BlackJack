#include <iostream>
#include "include/Game.h"

#include "include/Deck.h"
#include "include/Player.h"
#include "include/Dealer.h"

using namespace std;

int main() {

    Deck deck;
    deck.shuffle();
    // deck.printDeck();
    Dealer dealer;
    Player player;

    cout << "Dealing cards..." << endl;

    player.addCard(deck.deal());

    dealer.addCard(deck.deal());

    player.addCard(deck.deal());

    dealer.addCard(deck.deal());

    dealer.printFirstCard();

    cout << "Your hand: " << endl;
    player.printHand();
    cout<<"Hand value: " <<player.getHandValue()<<endl;
    player.playTurn(deck);

    
    dealer.playTurn(deck);


    return 0;
}