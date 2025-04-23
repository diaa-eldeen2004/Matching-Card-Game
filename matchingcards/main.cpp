// main.cpp
#include <QApplication>
#include "matchinggame.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MatchingGame game;
    game.show();  // Show the game window

    return app.exec();  // Start the Qt event loop
}
