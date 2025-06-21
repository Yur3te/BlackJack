#ifndef STANDCOMMAND_H
#define STANDCOMMAND_H

#include "Command.h"
#include "Game.h"
#include "mainwindow.h"

class StandCommand : public Command {
    public:
        StandCommand(Game* game, MainWindow* window);
        void execute() override;

    private:
        Game* game;
        MainWindow* window;
};

#endif // STANDCOMMAND_H