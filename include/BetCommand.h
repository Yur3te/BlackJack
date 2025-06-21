#ifndef BETCOMMAND_H
#define BETCOMMAND_H

#include "Command.h"
#include "Game.h"
#include "mainwindow.h"

class BetCommand : public Command {
    public:
        BetCommand(Game* game, MainWindow* window);
        void execute() override;
    private:
        Game* game;
        MainWindow* window;

};

#endif // BETCOMMAND_H