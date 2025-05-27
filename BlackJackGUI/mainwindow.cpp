#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);
    game = new Game();
    updateChipsDisplay();
    ui->textOutput->append("Gra rozpoczęta!");

    connect(ui->buttonHit, &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(ui->buttonStand, &QPushButton::clicked, this, &MainWindow::onStandClicked);
    connect(ui->buttonBet, &QPushButton::clicked, this, &MainWindow::onBetClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::onHitClicked()
{
    Card* card = game->playerHit();
    displayCard(card, ui->playerCardsWidget->layout());  
    ui->textOutput->append(QString::fromStdString("Dobierasz kartę: " + card->getImageName()));
    if (game->isPlayerBusted()) {
        game->determineOutcome();
        updateChipsDisplay();
        displayRoundResult();
    }
}

void MainWindow::onStandClicked()
{
   if (game->playerStand()) {
        game->dealerPlayTurn();
        updateHandsDisplay();
        game->determineOutcome();
        updateChipsDisplay();
        displayRoundResult();
        ui->textOutput->append("Gracz kończy turę.");
    }
}

void MainWindow::onBetClicked()
{
    int bet = ui->enterChips->text().toInt();
    if (bet > 0) {
        game->placeBet(bet);
        ui->textOutput->append(QString("Postawiono zakład: %1").arg(bet));
        ui->enterChips->clear();
        updateChipsDisplay();
    } else {
        ui->textOutput->append("Nieprawidłowy zakład!");
    }
    game->endRound();
    game->dealInitialCards();
    updateHandsDisplay();
    // game.checkBlackjack();
}

void MainWindow::displayCard(Card* card, QLayout* targetLayout) {
    QString imagePath = QCoreApplication::applicationDirPath() + "/assets/cards/" + QString::fromStdString(card->getImageName());
    QPixmap pixmap(imagePath);

    if (pixmap.isNull()) {
        qDebug() << "Błąd ładowania obrazu z:" << imagePath;
    } else {
        QLabel* cardLabel = new QLabel(this);
        cardLabel->setPixmap(pixmap.scaled(100, 140)); 
        targetLayout->addWidget(cardLabel);
    }
}

void MainWindow::updateChipsDisplay() {
    ui->chipsLabel->setText(QString("Chips: %1").arg(game->getChipsAmount()));
}

void MainWindow::displayRoundResult() {
    ui->textOutput->append(game->determineOutcome());
}



void MainWindow::updateHandsDisplay()
{
    // Czyść stare karty
    QLayoutItem* item;
    while ((item = ui->playerCardsWidget->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    while ((item = ui->dealerCardsWidget->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Wyświetl nowe karty
    for (Card* card : game->getPlayer().getFirstHand().getCards()) {
        displayCard(card, ui->playerCardsWidget->layout());
    }

    for (Card* card : game->getDealer().getFirstHand().getCards()) {
        displayCard(card, ui->dealerCardsWidget->layout());
    }
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


// void MainWindow::displayPlayerHand() {
    // ui->textOutput->append("Twoja ręka:");
    // for (Card* card : game->getPlayerHand()) {
    //     displayCard(card);
    // }
// }

// void MainWindow::displayDealerHand() {
    // ui->textOutput->append("Ręka krupiera:");
    // for (Card* card : game->getDealerHand()) {
    //     displayCard(card);
    // }
// }
