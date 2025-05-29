# Qt Memory Card Game 🃏
Description:Qt Memory Card Game is an engaging desktop application developed with Qt Creator using the Qt framework (C++ and Qt Widgets). This classic memory-matching game challenges players to pair identical cards in a 4x4 grid, testing their memory and focus. Featuring a vibrant interface, the game tracks time, score, and turns, and provides feedback on matches. Players flip cards to find pairs, earning points for matches while racing against the clock! 🕒
Features:  

Card Flipping 🔄: Flip two cards at a time to find matching pairs (A-H).  
Score Tracking ⭐: Earn 150 points per match, with a maximum score of 1200 for all 8 pairs.  
Time Tracking ⏱️: Displays elapsed time during gameplay.  
Dynamic UI 🎨: Cards change colors when flipped, with unmatched cards flipping back after a brief delay.  
Game Controls ▶️: Start a new game or cancel to exit.  
Win Condition 🏆: Displays a congratulatory message with turn count when all pairs are matched.

Technologies Used:  

C++ 💻: Core language for game logic and functionality.  
Qt Framework 🖼️: Powers the GUI with Qt Widgets, timers, and signals/slots.  
Qt Creator 🛠️: Used as the IDE for building and designing the application.  
Qt Classes: Utilizes QTimer, QPushButton, QLabel, QGridLayout, QHBoxLayout, QVBoxLayout, QMessageBox, and QApplication.

How It Works:  

The game initializes a 4x4 grid with 16 cards (8 pairs, labeled A-H), shuffled randomly.  
Players click cards to flip them, revealing their values with distinct colors.  
A QTimer updates the elapsed time every second and handles card flip-back delays.  
Matches increase the score by 150; mismatches flip back after 1 second.  
The game ends when all pairs are matched, showing a message with the turn count.  
Players can start a new game or cancel to exit the application.

Usage:  

Click "Start" to begin the game and enable card interactions.  
Click two cards to flip them and check for a match.  
Matched cards stay visible; unmatched cards flip back after a delay.  
Monitor your score and time in the UI.  
Complete all matches to win, or click "Cancel" to exit.

Dependencies:  

Qt 5 or later (Qt Widgets module) 📦  
C++11 or later

File Structure:  

MatchingGame.h: Declares the MatchingGame class with member variables and functions.  
MatchingGame.cpp: Implements the game logic, UI setup, card shuffling, and timer management.  
main.cpp: Entry point to launch the MatchingGame widget.

Future Improvements:  

Add sound effects for card flips and matches 🎶  
Include difficulty levels with larger grids or time limits ⏳  
Save high scores for persistence 🥇  
Enhance the UI with animations or custom card designs ✨

License:MIT License  
Contributing:Contributions are welcome! 🙌 Please submit a pull request or open an issue to discuss improvements or bugs.
