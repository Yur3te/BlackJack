#include "../include/Chips.h"

#include <fstream>
#include <QCoreApplication>

using namespace std;


Chips::Chips() {
    chips = 1000;
}

Chips::~Chips() {}

void Chips::addChips(int amount) {
    chips += amount;
}

void Chips::removeChips(int amount) {
    chips -= amount;
}

int Chips::getChips() const {
    return chips;
}

void Chips::printChips() const {
    std::cout << "Chips: " << chips << std::endl;
}

void Chips::saveChips() const {
    QString path = QCoreApplication::applicationDirPath() + "/chips.txt";
    ofstream file(path.toStdString());
    file << chips;
    file.close();
}

void Chips::loadChips() {
    QString path = QCoreApplication::applicationDirPath() + "/chips.txt";
    ifstream file(path.toStdString());
    file >> chips;
    file.close();
}

