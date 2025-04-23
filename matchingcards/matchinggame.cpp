#include "MatchingGame.h"
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>
#include <QApplication>  // Include QApplication header

MatchingGame::MatchingGame(QWidget *parent)
    : QWidget(parent), score(0), turns(0), timeElapsed(0), gameStarted(false)
{
    // Initialize cards and shuffle them
    initializeCards();
    shuffleCards();

    // Create a vertical layout for the main UI
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Title section
    QLabel *titleLabel = new QLabel("Memory Card Game", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 24, QFont::Bold));
    mainLayout->addWidget(titleLabel);

    // Create a horizontal layout for time and score
    QHBoxLayout *infoLayout = new QHBoxLayout();

    // Time label
    timeLabel = new QLabel("Time: 0", this);
    timeLabel->setFont(QFont("Arial", 14));
    timeLabel->setStyleSheet("color: red;");  // Set time label text color to red
    infoLayout->addWidget(timeLabel);

    // Add space between time and score
    infoLayout->addSpacerItem(new QSpacerItem(50, 20));  // Add a horizontal spacer

    // Score label
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setFont(QFont("Arial", 14));
    scoreLabel->setStyleSheet("color: blue;");  // Set score label text color to blue
    infoLayout->addWidget(scoreLabel);

    mainLayout->addLayout(infoLayout);

    // Create a grid layout for buttons (cards)
    QGridLayout *gridLayout = new QGridLayout();
    for (size_t i = 0; i < 16; ++i) {  // Use size_t instead of int to avoid signed/unsigned comparison warning
        buttons[i] = new QPushButton("*", this);
        buttons[i]->setFixedSize(50, 50);
        buttons[i]->setFont(QFont("Arial", 20));
        buttons[i]->setEnabled(false);  // Disable all cards initially
        gridLayout->addWidget(buttons[i], i / 4, i % 4);

        // Connect the button click event to the card selection function
        connect(buttons[i], &QPushButton::clicked, [this, i]() {
            if (!gameStarted || flipped[i]) return; // Ignore if game is not started or card is already flipped

            flipped[i] = true;
            buttons[i]->setText(QString(cards[i]));
            buttons[i]->setStyleSheet(QString("color: %1;").arg(cardColors[cards[i]].name())); // Set text color for card

            selectedCards.push(i);

            // If two cards are selected, check for a match
            if (selectedCards.size() == 2) {
                int first = selectedCards.top(); selectedCards.pop();
                int second = selectedCards.top(); selectedCards.pop();

                if (checkMatch(first, second)) {
                    score += 150;  // Increase the score by 150
                    scoreLabel->setText(QString("Score: %1").arg(score));

                    if (score == 8 * 150) {
                        timer->stop();  // Stop the timer when all pairs are matched
                        QMessageBox::information(this, "Game Over", QString("Congratulations! You've matched all pairs in %1 turns.").arg(turns));
                    }
                } else {
                    // If no match, flip them back after a delay using a queue
                    movesQueue.push({first, second});
                    QTimer::singleShot(1000, this, &MatchingGame::flipBackCards);
                }
                turns++;
            }

            updateUI();
        });
    }

    // Add the grid layout for the cards
    mainLayout->addLayout(gridLayout);

    // Add a Start and Cancel button
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *startButton = new QPushButton("Start", this);
    connect(startButton, &QPushButton::clicked, this, &MatchingGame::startGame);
    buttonLayout->addWidget(startButton);

    QPushButton *cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, &QPushButton::clicked, this, &MatchingGame::cancelGame);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Set the layout for the widget
    setLayout(mainLayout);

    // Set window properties
    setWindowTitle("Memory Card Game");
    setFixedSize(400, 400);

    // Timer setup
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MatchingGame::updateTime);
}

MatchingGame::~MatchingGame() {}

void MatchingGame::initializeCards()
{
    char values[] = { 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', 'G', 'G', 'H', 'H' };
    for (size_t i = 0; i < 16; ++i) {  // Use size_t instead of int
        cards.push_back(values[i]);
        flipped.push_back(false);
    }
}

void MatchingGame::shuffleCards()
{
    srand(static_cast<unsigned>(time(0)));
    for (size_t i = 0; i < cards.size(); ++i) {  // Use size_t instead of int
        int j = rand() % cards.size();
        std::swap(cards[i], cards[j]);
    }
}

bool MatchingGame::checkMatch(int first, int second)
{
    return cards[first] == cards[second];
}

void MatchingGame::flipBackCards()
{
    if (!movesQueue.empty()) {
        // Get the pair of cards to flip back
        auto [first, second] = movesQueue.front();
        movesQueue.pop();

        flipped[first] = flipped[second] = false;
        buttons[first]->setText("*");
        buttons[second]->setText("*");
        buttons[first]->setStyleSheet("color: black;");
        buttons[second]->setStyleSheet("color: black;");
    }

    updateUI();
}

void MatchingGame::updateUI()
{
    // Update the display of all the buttons based on the flipped state
    for (size_t i = 0; i < 16; ++i) {  // Use size_t instead of int
        if (flipped[i]) {
            buttons[i]->setText(QString(cards[i]));
            buttons[i]->setStyleSheet(QString("color: %1;").arg(cardColors[cards[i]].name())); // Set text color for card
        } else {
            buttons[i]->setText("*");
            buttons[i]->setStyleSheet("color: black;");
        }
    }
}

void MatchingGame::updateTime()
{
    if (gameStarted) {
        timeElapsed++;
        timeLabel->setText(QString("Time: %1").arg(timeElapsed));
    }
}

void MatchingGame::startGame()
{
    // Start the game and the timer
    gameStarted = true;
    timer->start(1000); // Start the timer (update every second)

    // Enable the card buttons for interaction
    for (size_t i = 0; i < 16; ++i) {  // Use size_t instead of int
        buttons[i]->setEnabled(true);
    }

    score = 0;
    turns = 0;
    timeElapsed = 0;
    updateUI();
}

void MatchingGame::cancelGame()
{
    // Stop the game and reset
    timer->stop();
    QApplication::quit();
}
