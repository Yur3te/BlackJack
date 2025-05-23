CONFIG += c++17

QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../include

SOURCES += \
    main.cpp \
    ../src/Card.cpp \
    ../src/Chips.cpp \
    ../src/Dealer.cpp \
    ../src/Deck.cpp \
    ../src/Game.cpp \
    ../src/Hand.cpp \
    ../src/Person.cpp \
    ../src/Player.cpp \
    mainwindow.cpp

HEADERS += \
    ../include/Card.h \
    ../include/Chips.h \
    ../include/Dealer.h \
    ../include/Deck.h \
    ../include/Game.h \
    ../include/Hand.h \
    ../include/Person.h \
    ../include/Player.h \
    mainwindow.h


# Jeśli nie masz UI (czyli nie masz pliku .ui), usuń FORMS:
FORMS += mainwindow.ui
