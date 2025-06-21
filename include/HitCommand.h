#ifndef HITCOMMAND_H
#define HITCOMMAND_H

#include "Command.h"
#include "Game.h"
#include "../BlackJackGUI/mainwindow.h"


class HitCommand : public Command {
    public:
        HitCommand(Game* game, MainWindow* window);
        void execute() override;

    private:
        Game* game;
        MainWindow* window;
};

#endif // HITCOMMAND_H