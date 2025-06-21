#include "../include/BetCommand.h"

#include <iostream>

BetCommand::BetCommand(Game* game, MainWindow* window) {
    this->game = game;
    this->window = window;
}

void BetCommand::execute() {
    if (!game->isRoundOver()) {
        window->appendTextOutput("Game is not over yet, you can't place a bet now.");
    } else if (game->getChipsAmount() <= 0) {
        window->appendTextOutput("You have no chips left to place a bet.");
        window->clearChipsInput();
        window->updateChipsDisplay();
        return;
    } else {
        int bet = window->getEnteredChips();
        if (game->getChipsAmount() < bet) {
            window->appendTextOutput("You don't have enough chips to place this bet.");
            window->clearChipsInput();
            window->updateChipsDisplay();
            return;
        }
        if (bet > 0) {
            game->placeBet(bet);
            window->appendTextOutput(QString("Placed a bet: %1").arg(bet));
            window->clearChipsInput();

            window->updateChipsDisplay();
            game->roundOver = false;

            game->endRound();
            game->dealInitialCards();
            window->displayHandValue(game->getPlayer().getFirstHand());
            window->updateHandsDisplay();
            QString bjMessage = game->checkBlackjack();
            if (!bjMessage.isEmpty()) {
                window->appendTextOutput(bjMessage);
                window->updateChipsDisplay();
                window->updateHandsDisplay();
                return;
            }
        } else {
            window->appendTextOutput("Something went wrong!");
        }

    }
}