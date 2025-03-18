#include "../include/Chips.h"

#include <fstream>

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
    ofstream file("chips.txt");
    file << chips;
    file.close();
}

void Chips::loadChips() {
    ifstream file("chips.txt");
    file >> chips;
    file.close();
}

