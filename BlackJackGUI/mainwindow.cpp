#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "HitCommand.h"
#include "StandCommand.h"
#include "BetCommand.h"
#include "DoubleDownCommand.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);
    game = new Game();
    updateChipsDisplay();
    ui->textOutput->append("Gra rozpoczęta!");

    hitCommand = new HitCommand(game, this);
    standCommand = new StandCommand(game, this);
    betCommand = new BetCommand(game, this);
    doubleDownCommand = new DoubleDownCommand(game, this);

    connect(ui->buttonHit, &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(ui->buttonStand, &QPushButton::clicked, this, &MainWindow::onStandClicked);
    connect(ui->buttonBet, &QPushButton::clicked, this, &MainWindow::onBetClicked);
    connect(ui->buttonDoubleDown, &QPushButton::clicked, this, &MainWindow::onDoubleDownClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;

    delete hitCommand;
    delete standCommand;
    delete betCommand;
    delete doubleDownCommand;
}

void MainWindow::onHitClicked()
{
    hitCommand->execute();
}

void MainWindow::onStandClicked()
{
    standCommand->execute();
}

void MainWindow::onDoubleDownClicked()
{
    doubleDownCommand->execute();
}

void MainWindow::onBetClicked()
{
    betCommand->execute();
    
}

void MainWindow::displayCard(Card* card, QWidget* targetWidget, int cardIndex, bool horizontal) {
    QString imagePath = QCoreApplication::applicationDirPath() + "/assets/cards/" + QString::fromStdString(card->getImageName());
    QPixmap pixmap(imagePath);

    if (pixmap.isNull()) {
        qDebug() << "Błąd ładowania obrazu z:" << imagePath;
    } else {
        // QLabel* cardLabel = new QLabel(this);
        // cardLabel->setPixmap(pixmap.scaled(100, 140)); 
        // targetLayout->addWidget(cardLabel);

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
        qDebug() << "Błąd ładowania obrazu z:" << imagePath;
    } else {
        // QLabel* cardLabel = new QLabel(this);
        // cardLabel->setPixmap(pixmap.scaled(100, 140)); 
        // targetLayout->addWidget(cardLabel);

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



void MainWindow::displayHandValue(const Hand& hand) {
    int value = hand.getHandValue();
    ui->handValue->setText(QString("value: %1").arg(value));
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


void MainWindow::updateHandsDisplay()
{
    // Czyść stare karty
    for (QObject* obj : ui->playerCardsWidget->children()) {
        QLabel* label = qobject_cast<QLabel*>(obj);
        if (label) delete label;
    }

    for (QObject* obj : ui->dealerCardsWidget->children()) {
        QLabel* label = qobject_cast<QLabel*>(obj);
        if (label) delete label;
    }


    // Wyświetl nowe karty
    const Hand& playerHand = game->getPlayer().getFirstHand();
    int i = 0;
    for (Card* card : playerHand.getCards()) {
        displayCard(card, ui->playerCardsWidget, i++, false);
    }

    // Dealer – jeśli gra trwa, pokaż 1. kartę + zakrytą
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

void MainWindow::showPlayerHandValue(const Hand& hand) {
    displayHandValue(hand);
}

void MainWindow::refreshChips() {
    updateChipsDisplay();
}




// void MainWindow::displayHands() {
//     ui->handsLayout->clear(); // Wyczyść poprzednią zawartość

//     for (int i = 0; i < game->player.getHandsCount(); ++i) {
//         // Stwórz kontener na rękę
//         QGroupBox* handGroup = new QGroupBox(QString("Ręka %1").arg(i + 1), this);
//         QVBoxLayout* handLayout = new QVBoxLayout(handGroup);

//         // Pokaż karty w tej ręce
//         Hand& hand = game->player.getHand(i);
//         for (Card* card : hand.getCards()) {
//             displayCard(card);  // Wyświetl kartę (metoda jak wcześniej)
//         }

//         ui->handsLayout->addWidget(handGroup);  // Dodaj rękę do głównego layoutu
//     }
// }

