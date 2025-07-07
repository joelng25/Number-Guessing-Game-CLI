#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int diff;
int answer;
int guess, guess_count, attempts = 1;

int main() {
  cout << "Welcome to the Number Guessing Game!" << endl
       << "I'm thinking of a number between 1 and 100." << endl
       << "You have 5 chances to guess the correct number." << endl
       << endl;

  string play_again = "Y";
  while (play_again[0] == 'Y' or play_again[0] == 'y') {
    cout << "Please select the difficulty level:" << endl
         << "1. Easy (10 chances)" << endl
         << "2. Medium (5 chances)" << endl
         << "3. Hard (3 chances)" << endl
         << endl;

    cout << "Enter your choice: ";

    while (!(cin >> diff) || diff < 1 || diff > 3) {
      if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter a number between 1 and 3: ";
      } else {
        cout << "Invalid choice! Please enter 1, 2, or 3: ";
      }
    }

    switch (diff) {
      case 1:
        cout << "Great! You have selected the Easy difficulty level." << endl;
        guess_count = 10;
        break;

      case 2:
        cout << "Great! You have selected the Medium difficulty level." << endl;
        guess_count = 5;
        break;

      case 3:
        cout << "Great! You have selected the Hard difficulty level." << endl;
        guess_count = 3;
        break;

      default:
        cout << "Invalid choice. Defaulting to Medium difficulty." << endl;
        guess_count = 5;
        break;
    }

    cout << "Let's start the game!" << endl;

    srand(time(0));
    answer = rand() % 100 + 1;
    attempts = 1;

    auto start = chrono::high_resolution_clock::now();
    bool solved = false;
    while (guess_count != (attempts - 1) and !solved) {
      cout << "Enter your guess: ";
      while (!(cin >> guess) || guess < 1 || guess > 100) {
        if (cin.fail()) {
          cin.clear();
          cin.ignore(10000, '\n');
          cout << "Invalid input! Please enter a number between 1 and 100: ";
        } else {
          cout << "Number out of range! Please enter a number between 1 and 100: ";
        }
      }

      if (guess == answer) {
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "Congratulations! You guessed the correct number in " << attempts << " attempts."
             << endl;
        cout << "Time taken: " << elapsed.count() << " seconds." << endl;
        solved = true;
      } else if (guess < answer) {
        cout << "Incorrect! The number is greater than " << guess << "." << endl;
      } else {
        cout << "Incorrect! The number is less than " << guess << "." << endl;
      }
      ++attempts;
    }
    cout << "Want to play again? (Write Y or N)" << endl;
    cin >> play_again;
  }
  return 1;
}