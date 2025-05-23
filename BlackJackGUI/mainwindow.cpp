#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();
    ui->textOutput->append("Gra rozpoczęta!");

    connect(ui->buttonHit, &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(ui->buttonStand, &QPushButton::clicked, this, &MainWindow::onStandClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::onHitClicked()
{
    Card* card = game->playerHit();
    displayCard(card);  
    ui->textOutput->append(QString::fromStdString("Dobierasz kartę: " + card->getImageName()));
    if (game->isPlayerBusted()) {
        ui->textOutput->append("Przegrałeś, masz powyżej 21!");
    }
}

void MainWindow::onStandClicked()
{
   if (game->playerStand()) {
        ui->textOutput->append("Gracz kończy turę.");
    }
}

void MainWindow::displayCard(Card* card) {
    // QString imagePath = "../assets/cards/" + QString::fromStdString(card->getImageName());
    // QLabel* cardLabel = new QLabel(this);
    // cardLabel->setPixmap(QPixmap(imagePath).scaled(100, 140));
    // ui->cardsLayout->addWidget(cardLabel);

    QString imagePath = QCoreApplication::applicationDirPath() + "/assets/cards/" + QString::fromStdString(card->getImageName());
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        qDebug() << "Błąd ładowania obrazu z:" << imagePath;
    } else {
        QLabel* cardLabel = new QLabel(this);
        cardLabel->setPixmap(pixmap.scaled(100, 140)); 
        ui->cardsLayout->addWidget(cardLabel);
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


void MainWindow::displayPlayerHand() {
    // ui->textOutput->append("Twoja ręka:");
    // for (Card* card : game->getPlayerHand()) {
    //     displayCard(card);
    // }
}

void MainWindow::displayDealerHand() {
    // ui->textOutput->append("Ręka krupiera:");
    // for (Card* card : game->getDealerHand()) {
    //     displayCard(card);
    // }
}
