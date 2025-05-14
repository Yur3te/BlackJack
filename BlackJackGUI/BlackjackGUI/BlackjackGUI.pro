QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Jeśli nie używasz Qt GUI (np. tylko logika gry), usuń te linijki:
# QT += gui
# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    ../main.cpp \
    ../src/Card.cpp \
    ../src/Chips.cpp \
    ../src/Dealer.cpp \
    ../src/Deck.cpp \
    ../src/Game.cpp \
    ../src/Hand.cpp \
    ../src/Person.cpp \
    ../src/Player.cpp
HEADERS += \
    ../include/Card.h \
    ../include/Chips.h \
    ../include/Dealer.h \
    ../include/Deck.h \
    ../include/Game.h \
    ../include/Hand.h \
    ../include/Person.h \
    ../include/Player.h

# Jeśli nie masz UI (czyli nie masz pliku .ui), usuń FORMS:
# FORMS += mainwindow.ui
