#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
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
    void refreshChips();
    void displayRoundResult();
    void updateChipsDisplay();
    void updateHandsDisplay();
    void displayHandValue(const Hand& hand, const QString& labelName);
    void clearLabel(const QString& labelName);
    void clearChipsInput();
    int getEnteredChips() const;
    int getEnteredChipsToAdd() const;
    

private slots:
    void onCommandClicked(Command* command);

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
    Command* addChipsCommand;
    
};
#endif // MAINWINDOW_H