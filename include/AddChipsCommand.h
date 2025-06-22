#ifndef ADDCHIPSCOMMAND_h
#define ADDCHIPSCOMMAND_H

#include "Command.h"
#include "Game.h"
#include "mainwindow.h"

class AddChipsCommand : public Command {
    public:
        AddChipsCommand(Game* game, MainWindow* window);
        void execute() override;
    private:
        Game* game;
        MainWindow* window;

};

#endif // ADDCHIPSCOMMAND_H