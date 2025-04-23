#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <stack>
#include <queue>

using namespace std;


void initializeCards(vector<char>& cards) {
    char values[] = { 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', 'G', 'G', 'H', 'H' };
    for (int i = 0; i < 16; ++i) {
        cards.push_back(values[i]);
    }
}


void shuffleCards(vector<char>& cards) {
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < cards.size(); ++i) {
        int j = rand() % cards.size();
        swap(cards[i], cards[j]);
    }
}

// Function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Unix/Linux
#endif
}


void displayBoard(const vector<char>& cards, const vector<bool>& flipped) {
    cout << "Current Board:\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (flipped[i * 4 + j]) {
                cout << setw(2) << cards[i * 4 + j] << " ";
            }
            else {
                cout << setw(2) << "*" << " ";
            }
        }
        cout << endl;
    }
}


bool checkMatch(const vector<char>& cards, int first, int second) {
    return cards[first] == cards[second];
}

int main() {
    char choice;
    do {
        vector<char> cards;
        vector<bool> flipped(16, false);
        initializeCards(cards);
        shuffleCards(cards);

        int score = 0;
        int turns = 0;

        while (score < 8) {
            clearScreen();
            displayBoard(cards, flipped);

            int firstCard, secondCard;

            cout << "Turn " << turns + 1 << " - Enter first card (0-15): ";
            cin >> firstCard;

            if (firstCard < 0 || firstCard >= 16 || flipped[firstCard]) {
                cout << "Invalid input or card already matched! Try again.\n";
                continue;
            }

            cout << "Enter second card (0-15): ";
            cin >> secondCard;

            if (secondCard < 0 || secondCard >= 16 || flipped[secondCard] || firstCard == secondCard) {
                cout << "Invalid input or card already matched! Try again.\n";
                continue;
            }

            flipped[firstCard] = true;
            flipped[secondCard] = true;

            clearScreen();
            displayBoard(cards, flipped);

            if (checkMatch(cards, firstCard, secondCard)) {
                cout << "It's a match!\n";
                score++;
            }
            else {
                cout << "Not a match! Try again.\n";

                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();

                flipped[firstCard] = false;
                flipped[secondCard] = false;
            }

            turns++;
        }

        cout << "Congratulations! You've matched all pairs in " << turns << " turns.\n";
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}