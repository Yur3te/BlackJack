#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onHitClicked();
    void onStandClicked();
    void displayCard(Card* card);
    void displayPlayerHand();
    void displayDealerHand();

private:
    Ui::MainWindow *ui;
    Game* game;
    Deck* deck;
};
#endif // MAINWINDOW_H