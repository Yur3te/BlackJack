#include "../include/StandCommand.h"

#include <iostream>
StandCommand::StandCommand(Game* game, MainWindow* window) {
    this->game = game;
    this->window = window;
}
void StandCommand::execute() {
    if (game->isRoundOver()) {
        window->appendTextOutput("You can't stand, the round is over. Please place a new bet.");
        return;
    }

   if (game->playerStand()) {
        game->roundOver = true;
        game->dealerPlayTurn();
        window->updateHandsDisplay();
        game->determineOutcome();
        window->updateChipsDisplay();
        window->displayRoundResult();
        window->appendTextOutput("Gracz kończy turę.");
    }
}