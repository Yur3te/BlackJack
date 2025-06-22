#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "HitCommand.h"
#include "StandCommand.h"
#include "BetCommand.h"
#include "DoubleDownCommand.h"
#include "AddChipsCommand.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);
    setWindowTitle("BlackJack 🃏");
    game = new Game();
    updateChipsDisplay();
    ui->textOutput->append("Game started!");

    hitCommand = new HitCommand(game, this);
    standCommand = new StandCommand(game, this);
    betCommand = new BetCommand(game, this);
    doubleDownCommand = new DoubleDownCommand(game, this);
    addChipsCommand = new AddChipsCommand(game, this);

    connect(ui->buttonHit, &QPushButton::clicked,  [=]() { onCommandClicked(hitCommand); });
    connect(ui->buttonStand, &QPushButton::clicked, [=]() { onCommandClicked(standCommand); });
    connect(ui->buttonBet, &QPushButton::clicked, [=]() { onCommandClicked(betCommand); });
    connect(ui->buttonDoubleDown, &QPushButton::clicked, [=]() { onCommandClicked(doubleDownCommand); });
    connect(ui->buttonAddChips, &QPushButton::clicked, [=]() { onCommandClicked(addChipsCommand); });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;

    delete hitCommand;
    delete standCommand;
    delete betCommand;
    delete doubleDownCommand;
    delete addChipsCommand;
}

void MainWindow::onCommandClicked(Command* command)
{
    command->execute();
}


void MainWindow::displayCard(Card* card, QWidget* targetWidget, int cardIndex, bool horizontal) {
    QString imagePath = QCoreApplication::applicationDirPath() + "/assets/cards/" + QString::fromStdString(card->getImageName());
    QPixmap pixmap(imagePath);

    if (pixmap.isNull()) {
        qDebug() << "Error while loading: " << imagePath;
    } else {
        QLabel* cardLabel = new QLabel(targetWidget);
        cardLabel->setPixmap(pixmap.scaled(100, 140));
        cardLabel->setScaledContents(true);
        cardLabel->resize(100, 140);

        int xOffset = horizontal ? cardIndex * 100 : 0;
        int yOffset = horizontal ? 0 : cardIndex * 30;
        cardLabel->move(xOffset, yOffset);
        cardLabel->show();
    }
}

void MainWindow::displayBackCard(QWidget* targetWidget, int cardIndex, bool horizontal) {
    QString imagePath = QCoreApplication::applicationDirPath() + "/assets/cards/back_of_card.png";
    QPixmap pixmap(imagePath);

    if (pixmap.isNull()) {
        qDebug() << "Error while loading: " << imagePath;
    } else {
        QLabel* cardLabel = new QLabel(targetWidget);
        cardLabel->setPixmap(pixmap.scaled(100, 140));
        cardLabel->setScaledContents(true);
        cardLabel->resize(100, 140);

        int xOffset = horizontal ? cardIndex * 100 : 0;
        int yOffset = horizontal ? 0 : cardIndex * 30;
        cardLabel->move(xOffset, yOffset);
        cardLabel->show();
    }
}


void MainWindow::updateChipsDisplay() {
    ui->chipsLabel->setText(QString("Chips: %1").arg(game->getChipsAmount()));
}



void MainWindow::displayHandValue(const Hand& hand, const QString& handName) {
    QLabel* handLabel = findChild<QLabel*>(handName);
    if (!handLabel) {
        qDebug() << "Can't find label!" << handName;
        return;
    }
    int value = hand.getHandValue();
    handLabel->setText(QString("value: %1").arg(value));
}

void MainWindow::clearLabel(const QString& labelName) {
    QLabel* label = findChild<QLabel*>(labelName);
    if (label) {
        label->clear();
    } else {
        qDebug() << "Can't find label!" << labelName;
    }
}

void MainWindow::displayRoundResult() {
    ui->textOutput->append(game->determineOutcome());
}

void MainWindow::clearChipsInput() {
    ui->enterChips->clear();
}

int MainWindow::getEnteredChips() const {
    return ui->enterChips->text().toInt();
}

int MainWindow::getEnteredChipsToAdd() const {
    return ui->enteredChipsToAdd->text().toInt();
}

void MainWindow::updateHandsDisplay()
{
    for (QObject* obj : ui->playerCardsWidget->children()) {
        QLabel* label = qobject_cast<QLabel*>(obj);
        if (label) delete label;
    }

    for (QObject* obj : ui->dealerCardsWidget->children()) {
        QLabel* label = qobject_cast<QLabel*>(obj);
        if (label) delete label;
    }


    const Hand& playerHand = game->getPlayer().getFirstHand();
    int i = 0;
    for (Card* card : playerHand.getCards()) {
        displayCard(card, ui->playerCardsWidget, i++, false);
    }

    const Hand& dealerHand = game->getDealer().getFirstHand();
    if (!game->isRoundOver()) {
        if (!dealerHand.getCards().empty()) {
            displayCard(dealerHand.getCards()[0], ui->dealerCardsWidget, 0, true);
            displayBackCard(ui->dealerCardsWidget, 1, true);
        }
    } else {
        int j = 0;
        for (Card* card : dealerHand.getCards()) {
            displayCard(card, ui->dealerCardsWidget, j++, true);
        }
    }


}

void MainWindow::appendTextOutput(const QString& text) {
    ui->textOutput->append(text);
}

void MainWindow::showPlayerCard(Card* card) {
    displayCard(card, ui->playerCardsWidget, game->getPlayer().getFirstHand().getCards().size() - 1, false);
}

void MainWindow::refreshChips() {
    updateChipsDisplay();
}
