#include "../include/HitCommand.h"

#include <iostream>

HitCommand::HitCommand(Game* game, MainWindow* window) {
    this->game = game;
    this->window = window;
}

void HitCommand::execute() {
    if (game->isRoundOver()) {
        window->appendTextOutput("You can't hit, the round is over. Please place a new bet.");
        return;
    }
    Card* card = game->playerHit();
    window->showPlayerCard(card);
    window->displayHandValue(game->getPlayer().getFirstHand(), "playerHandValue");
    window->appendTextOutput(QString::fromStdString("Dobierasz kartę: " + card->getImageName()));
    if (game->isPlayerBusted()) {
        game->determineOutcome();
        window->refreshChips();
        window->displayRoundResult();
        window->displayHandValue(game->getDealer().getFirstHand(), "dealerHandValue");
        window->updateHandsDisplay();
    }
}
