#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int diff;
int answer;
int guess, guess_count, attempts = 1;

int main() {
  srand(time(0));
  answer = rand() % 100 + 1;

  cout << "Welcome to the Number Guessing Game!" << endl
       << "I'm thinking of a number between 1 and 100." << endl
       << "You have 5 chances to guess the correct number." << endl
       << endl;

  cout << "Please select the difficulty level:" << endl
       << "1. Easy(10 chances)" << endl
       << "2. Medium(5 chances)" << endl
       << "3. Hard(3 chances)" << endl
       << endl;

  cout << "Enter your choice: ";
  cin >> diff;

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
  }

  cout << "Let's start the game!" << endl;

  while (guess_count > 0) {
    cout << "Enter your guess: ";
    cin >> guess;

    if (guess == answer) {
      cout << "Congratulations! You guessed the correct number in " << attempts << " attempts."
           << endl;
      return 1;
    } else if (guess < answer) {
      cout << "Incorrect! The number is greater than " << guess << "." << endl;
    } else {
      cout << "Incorrect! The number is less than " << guess << "." << endl;
    }
    --guess_count;
    ++attempts;
  }
}