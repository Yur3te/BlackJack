#ifndef DOUBLEDOWNCOMMAND_H
#define DOUBLEDOWNCOMMAND_H

#include "Command.h"
#include "Game.h"
#include "mainwindow.h"

class DoubleDownCommand : public Command {
    public:
        DoubleDownCommand(Game* game, MainWindow* window);
        void execute() override;

    private:
        Game* game;
        MainWindow* window;
};

#endif // DOUBLEDOWNCOMMAND_H