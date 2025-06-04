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
    void onBetClicked();
    void onDoubleDownClicked();

    
    void displayCard(Card* card, QWidget* targetWidget, int cardIndex, bool horizontal);
    void displayBackCard(QWidget* targetWidget, int cardIndex, bool horizontal);
    void updateChipsDisplay();
    void displayHandValue(const Hand& hand);
    void updateHandsDisplay();
    void displayRoundResult();
    
    // void displayPlayerHand(const std::vector<Card>& cards);
    // void displayDealerHand(const std::vector<Card>& cards, bool revealAll);


private:
    Ui::MainWindow *ui;
    Game* game;
};
#endif // MAINWINDOW_H