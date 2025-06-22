#include "../include/AddChipsCommand.h"

#include <iostream>

AddChipsCommand::AddChipsCommand(Game* game, MainWindow* window) {
    this->game = game;
    this->window = window;
}

void AddChipsCommand::execute() {
    if (game->isRoundOver()) {
        int chipsToAdd = window->getEnteredChipsToAdd();
        if(game->getChipsAmount() > 0) {
            window->appendTextOutput("Why you give up? You have chips in your balance, don't lose hope!");
            return;
        }
        if (chipsToAdd > 0) {
            game->addChips(chipsToAdd);
            window->appendTextOutput(QString("Added %1 chips to your balance.").arg(chipsToAdd));
            window->updateChipsDisplay();
            window->clearChipsInput();
        } else {
            window->appendTextOutput("You must enter a positive number of chips to add.");
        }
    } else {
        window->appendTextOutput("You can't add chips during an active round.");
    }
}