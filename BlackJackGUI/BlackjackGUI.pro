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



CONFIG(debug, debug|release) {
    BUILD_DIR = debug
} else {
    BUILD_DIR = release
}

ASSETS_DIR = $$PWD/assets
BUILD_ASSETS_DIR = $$OUT_PWD/$$BUILD_DIR/assets

unix: {
    copy_assets.commands = cp -r $$ASSETS_DIR $$BUILD_ASSETS_DIR
    copy_assets.CONFIG += no_link target_predeps
    QMAKE_EXTRA_TARGETS += copy_assets
    PRE_TARGETDEPS += copy_assets
}

win32: {
    copy_assets.commands = xcopy /E /I /Y /Q \"$$ASSETS_DIR\" \"$$BUILD_ASSETS_DIR\"
    copy_assets.CONFIG += no_link target_predeps
    QMAKE_EXTRA_TARGETS += copy_assets
    PRE_TARGETDEPS += copy_assets
}
