#ifndef MATCHINGGAME_H
#define MATCHINGGAME_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <queue>
#include <vector>
#include <stack>
#include <QMap>
#include <QColor>

class MatchingGame : public QWidget
{
    Q_OBJECT

public:
    MatchingGame(QWidget *parent = nullptr);
    ~MatchingGame();

private:
    void initializeCards();
    void shuffleCards();
    bool checkMatch(int first, int second);
    void updateUI();
    void updateTime();
    void flipBackCards();

private slots:
    void startGame();
    void cancelGame();

private:
    std::vector<char> cards;  // The card values
    std::vector<bool> flipped;  // States of the cards (flipped or not)
    QPushButton *buttons[16];  // The buttons representing the cards
    QLabel *timeLabel;  // The label for displaying the time
    QLabel *scoreLabel;  // The label for displaying the score
    QTimer *timer;  // Timer to track the game time
    std::queue<std::pair<int, int>> movesQueue;  // Queue to store moves for flipping back cards
    int score;  // Number of matched pairs
    int turns;  // Number of turns taken
    int timeElapsed;  // Time elapsed since the game started
    bool gameStarted;  // Flag to check if the game has started
    std::stack<int> selectedCards;  // Stack to store selected cards for match check

    // Added to store the color for each card type
    QMap<char, QColor> cardColors;  // To store colors for each card
};

#endif // MATCHINGGAME_H
