#ifndef CHIPS_H
#define CHIPS_H

#include <iostream>
#include <string>
#include <fstream>


class Chips {
    public:
        Chips();
        ~Chips();
        void addChips(int amount);
        void removeChips(int amount);
        int getChips() const;
        void printChips() const;
        void saveChips() const;
        void loadChips();
    private:
        int chips;
};


#endif // CHIPS_H
