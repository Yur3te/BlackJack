#include "../include/DoubleDownCommand.h"

#include <iostream>

DoubleDownCommand::DoubleDownCommand(Game* game, MainWindow* window) {
    this->game = game;
    this->window = window;
}

void DoubleDownCommand::execute() {
    if (game->isRoundOver()) {
        window->appendTextOutput("You can't double down, the round is over. Please place a new bet.");
        return;
    }
    if (game->getPlayer().getFirstHand().getCards().size() != 2) {
        window->appendTextOutput("You can only double down on your first two cards.");
        return;
    }
    if (game->playerDoubleDown()) {
        game->roundOver = true;
        game->dealerPlayTurn();
        window->updateHandsDisplay();
        window->displayHandValue(game->getPlayer().getFirstHand());
        game->determineOutcome();
        window->updateChipsDisplay();
        window->displayRoundResult();
        window->appendTextOutput("You doubled down and ended your turn.");
    } else {
        window->appendTextOutput("You can't double down at this moment.");
    }
}