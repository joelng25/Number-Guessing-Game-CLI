#include <array>
#include <cctype>
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max();
const int MIN_NUM = 1;
const int MAX_NUM = 100;
const char* HIGHSCORE_FILE = "highscore.txt";

void printTries(int counter) {
  cout << "You have " << counter << " " << (counter == 1 ? "attempt" : "attempts") << " left."
       << endl
       << endl;
}

int readIntInRange(const string& prompt, int min_value, int max_value) {
  int value;
  while (true) {
    cout << prompt;
    if (cin >> value and value >= min_value and value <= max_value) {
      return value;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input! Please enter a number between " << min_value << " and " << max_value
         << "." << endl;
  }
}

char readYesNo(const string& prompt) {
  while (true) {
    string input;
    cout << prompt;
    if (cin >> input and !input.empty()) {
      char value = static_cast<char>(tolower(static_cast<unsigned char>(input[0])));
      if (value == 'y' or value == 'n') {
        return value;
      }
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid choice! Please enter Y or N." << endl;
  }
}

int attemptsForDifficulty(int diff) {
  switch (diff) {
    case 1:
      cout << "Great! You have selected the Easy difficulty level." << endl;
      return 10;
    case 2:
      cout << "Great! You have selected the Medium difficulty level." << endl;
      return 5;
    case 3:
      cout << "Great! You have selected the Hard difficulty level." << endl;
      return 3;
    default:
      cout << "Invalid choice. Defaulting to Medium difficulty." << endl;
      return 5;
  }
}

void showHint(int answer, int& range_hint_level) {
  if (range_hint_level >= 3) {
    cout << "All hints have been used already!" << endl;
    return;
  }

  const vector<int> widths = {10, 5, 3};
  int width = widths[range_hint_level];
  int low = max(MIN_NUM, answer - width);
  int high = min(MAX_NUM, answer + width);
  cout << "The number is between " << low << " and " << high << "." << endl;
  ++range_hint_level;
}

void loadHighscores(vector<int>& highscore) {
  ifstream in(HIGHSCORE_FILE);
  if (!in) {
    return;
  }

  for (int i = 0; i < 3; ++i) {
    int value;
    if (!(in >> value) || value <= 0) {
      highscore[i] = INF;
      return;
    }
    highscore[i] = value;
  }
}

void saveHighscores(const vector<int>& highscore) {
  ofstream out(HIGHSCORE_FILE, ios::trunc);
  if (!out) {
    cout << "Warning: Could not save highscores." << endl;
    return;
  }

  for (int i = 0; i < 3; ++i) {
    if (i > 0) {
      out << ' ';
    }
    out << highscore[i];
  }
}

int main() {
  cout << "Welcome to the Number Guessing Game!" << endl
       << "I'm thinking of a number between 1 and 100." << endl
       << "Select a difficulty to choose your number of chances." << endl
       << endl;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dist(MIN_NUM, MAX_NUM);

  vector<int> highscore(3, INF);
  loadHighscores(highscore);
  char play_again = 'y';

  while (play_again == 'y') {
    cout << "Please select the difficulty level:" << endl
         << "1. Easy (10 chances)" << endl
         << "2. Medium (5 chances)" << endl
         << "3. Hard (3 chances)" << endl
         << endl;

    int diff = readIntInRange("Enter your choice: ", 1, 3);
    cout << endl;

    int guess_count = attemptsForDifficulty(diff);

    cout << "Let's start the game!" << endl << endl;

    int answer = dist(gen);
    int attempts = 1;

    int range_hint_level = 0;

    auto start = chrono::high_resolution_clock::now();
    bool solved = false;
    while (attempts <= guess_count and !solved) {
      int guess = readIntInRange("Enter your guess: ", MIN_NUM, MAX_NUM);

      if (guess == answer) {
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "Congratulations! You guessed the correct number in " << attempts << " attempts."
             << endl;
        cout << "Time taken: " << elapsed.count() << " seconds." << endl << endl;
        if (highscore[diff - 1] > attempts) {
          highscore[diff - 1] = attempts;
          saveHighscores(highscore);
          cout << "New highscore!" << endl << endl;
        }
        solved = true;
      } else if (guess < answer) {
        cout << "Incorrect! The number is greater than " << guess << "." << endl;
        printTries(guess_count - attempts);
      } else {
        cout << "Incorrect! The number is less than " << guess << "." << endl;
        printTries(guess_count - attempts);
      }

      if (!solved and attempts < guess_count) {
        char clue = readYesNo("Do you want a hint? (Write Y(y) or N(n)): ");
        cout << endl;
        if (clue == 'y') {
          showHint(answer, range_hint_level);
        }
      }

      ++attempts;
    }

    if (!solved) {
      cout << "Game over! The correct number was " << answer << "." << endl << endl;
    }

    play_again = readYesNo("Want to play again? (Write Y or N): ");
    cout << endl;
  }

  return 0;
}