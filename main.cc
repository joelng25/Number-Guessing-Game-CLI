#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>

#include "game.h"

using namespace std;
using namespace game;

const char* HIGHSCORE_FILE = "highscore.txt";

void printTries(int left) {
  cout << "You have " << left << " " << (left == 1 ? "attempt" : "attempts") << " left." << endl
       << endl;
}

void discardLine() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readIntInRange(const string& prompt, int min_value, int max_value) {
  int value;
  while (true) {
    cout << prompt;
    if (cin >> value and value >= min_value and value <= max_value) {
      return value;
    }
    if (cin.eof()) exit(0);
    discardLine();
    cout << "Invalid input! Please enter a number between " << min_value << " and " << max_value
         << "." << endl;
  }
}

bool readYesNo(const string& prompt) {
  while (true) {
    string input;
    cout << prompt;
    if (cin >> input) {
      char value = static_cast<char>(tolower(static_cast<unsigned char>(input[0])));
      if (value == 'y' or value == 'n') return value == 'y';
    }
    if (cin.eof()) exit(0);
    discardLine();
    cout << "Invalid choice! Please enter Y or N." << endl;
  }
}

Highscores loadHighscores() {
  Highscores scores;
  scores.fill(NO_SCORE);
  ifstream in(HIGHSCORE_FILE);
  for (int& s : scores) {
    int value;
    if (!(in >> value) or value <= 0) break;
    s = value;
  }
  return scores;
}

void saveHighscores(const Highscores& scores) {
  ofstream out(HIGHSCORE_FILE, ios::trunc);
  if (!out) {
    cout << "Warning: Could not save highscores." << endl;
    return;
  }
  out << scores[0] << ' ' << scores[1] << ' ' << scores[2];
}

Difficulty chooseDifficulty() {
  cout << "Please select the difficulty level:" << endl
       << "1. Easy (10 chances)" << endl
       << "2. Medium (5 chances)" << endl
       << "3. Hard (3 chances)" << endl
       << endl;
  auto d = static_cast<Difficulty>(readIntInRange("Enter your choice: ", 1, 3));
  cout << endl << "Great! You have selected the " << nameOf(d) << " difficulty level." << endl;
  return d;
}

void playRound(mt19937& gen, Highscores& scores) {
  Difficulty difficulty = chooseDifficulty();
  int max_attempts = attemptsFor(difficulty);
  int answer = uniform_int_distribution<int>(MIN_NUM, MAX_NUM)(gen);
  int hints_used = 0;

  cout << "Let's start the game!" << endl << endl;
  auto start = chrono::steady_clock::now();

  for (int attempt = 1; attempt <= max_attempts; ++attempt) {
    int guess = readIntInRange("Enter your guess: ", MIN_NUM, MAX_NUM);

    if (guess == answer) {
      chrono::duration<double> elapsed = chrono::steady_clock::now() - start;
      cout << "Congratulations! You guessed the correct number in " << attempt
           << (attempt == 1 ? " attempt." : " attempts.") << endl
           << "Time taken: " << elapsed.count() << " seconds." << endl
           << endl;
      if (updateHighscore(scores, difficulty, attempt)) {
        saveHighscores(scores);
        cout << "New highscore!" << endl << endl;
      }
      return;
    }

    cout << "Incorrect! The number is " << (guess < answer ? "greater" : "less") << " than "
         << guess << "." << endl;
    printTries(max_attempts - attempt);

    if (attempt < max_attempts and readYesNo("Do you want a hint? (Y/N): ")) {
      cout << endl;
      if (hints_used >= MAX_HINTS) {
        cout << "All hints have been used already!" << endl;
      } else {
        auto [low, high] = hintRange(answer, hints_used++);
        cout << "The number is between " << low << " and " << high << "." << endl;
      }
    }
  }

  cout << "Game over! The correct number was " << answer << "." << endl << endl;
}

int main() {
  cout << "Welcome to the Number Guessing Game!" << endl
       << "I'm thinking of a number between " << MIN_NUM << " and " << MAX_NUM << "." << endl
       << "Select a difficulty to choose your number of chances." << endl
       << endl;

  mt19937 gen(random_device{}());
  Highscores scores = loadHighscores();

  do {
    playRound(gen, scores);
  } while (readYesNo("Want to play again? (Y/N): "));

  return 0;
}
