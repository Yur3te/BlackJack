#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Game.h"
#include "Command.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void appendTextOutput(const QString& text);
    void showPlayerCard(Card* card);
    void showPlayerHandValue(const Hand& hand);
    void refreshChips();
    void displayRoundResult();
    void updateChipsDisplay();
    void updateHandsDisplay();
    void displayHandValue(const Hand& hand);
    void clearChipsInput();
    int getEnteredChips() const;
    

private slots:
    void onHitClicked();
    void onStandClicked();
    void onBetClicked();
    void onDoubleDownClicked();


    void displayCard(Card* card, QWidget* targetWidget, int cardIndex, bool horizontal);
    void displayBackCard(QWidget* targetWidget, int cardIndex, bool horizontal);

    
    
    // void displayPlayerHand(const std::vector<Card>& cards);
    // void displayDealerHand(const std::vector<Card>& cards, bool revealAll);


private:
    Ui::MainWindow *ui;
    Game* game;
    Command* standCommand;
    Command* betCommand;
    Command* doubleDownCommand;
    Command* hitCommand;
    
};
#endif // MAINWINDOW_H