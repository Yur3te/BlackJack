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
    connect(ui->buttonDoubleDown, &QPushButton::clicked, this, &MainWindow::onDoubleDownClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::onHitClicked()
{
    if (game->isRoundOver()) {
        ui->textOutput->append("You can't hit, the round is over. Please place a new bet.");
        return;
    }
    Card* card = game->playerHit();
    displayCard(card, ui->playerCardsWidget, game->getPlayer().getFirstHand().getCards().size() - 1, false);
    displayHandValue(game->getPlayer().getFirstHand());
    ui->textOutput->append(QString::fromStdString("Dobierasz kartę: " + card->getImageName()));
    if (game->isPlayerBusted()) {
        game->determineOutcome();
        updateChipsDisplay();
        displayRoundResult();
    }
}

void MainWindow::onStandClicked()
{
    if (game->isRoundOver()) {
        ui->textOutput->append("You can't stand, the round is over. Please place a new bet.");
        return;
    }

   if (game->playerStand()) {
        game->roundOver = true;
        game->dealerPlayTurn();
        updateHandsDisplay();
        game->determineOutcome();
        updateChipsDisplay();
        displayRoundResult();
        ui->textOutput->append("Gracz kończy turę.");
    }
}

void MainWindow::onDoubleDownClicked()
{
    if(game->isRoundOver()) {
        ui->textOutput->append("You can't double down, the round is over. Please place a new bet.");
        return;
    }
    if (game->getPlayer().getFirstHand().getCards().size() != 2) {
        ui->textOutput->append("You can only double down on your first two cards.");
        return;
    }
    if (game->playerDoubleDown()) {
        game->roundOver = true;
        game->dealerPlayTurn();
        updateHandsDisplay();
        displayHandValue(game->getPlayer().getFirstHand());
        game->determineOutcome();
        updateChipsDisplay();
        displayRoundResult();
        ui->textOutput->append("You doubled down and ended your turn.");
    } else {
        ui->textOutput->append("You can't double down at this moment.");
    }
}

void MainWindow::onBetClicked()
{
    if (!game->isRoundOver()) {
        ui->textOutput->append("Game is not over yet, you can't place a bet now.");
    } else if (game->getChipsAmount() <= 0) {
        ui->textOutput->append("You have no chips left to place a bet.");
        ui->enterChips->clear();
        updateChipsDisplay();
        return;
    } else {
        int bet = ui->enterChips->text().toInt();
        if (bet > 0) {
            game->placeBet(bet);
            ui->textOutput->append(QString("Postawiono zakład: %1").arg(bet));
            ui->enterChips->clear();
            updateChipsDisplay();
            game->roundOver = false;

            game->endRound();
            game->dealInitialCards();
            displayHandValue(game->getPlayer().getFirstHand());
            updateHandsDisplay();
        // game.checkBlackjack();
        } else {
            ui->textOutput->append("Nieprawidłowy zakład!");
        }

    }
    
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
