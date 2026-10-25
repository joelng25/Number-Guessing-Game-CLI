# Number Guessing Game CLI

[![CI](https://github.com/joelng25/Number-Guessing-Game-CLI/actions/workflows/ci.yml/badge.svg)](https://github.com/joelng25/Number-Guessing-Game-CLI/actions/workflows/ci.yml)

A terminal game in C++: the computer picks a number between 1 and 100 and you try to guess it.

Project idea from [roadmap.sh](https://roadmap.sh/projects/number-guessing-game).

## Features

- Three difficulty levels: Easy (10 chances), Medium (5), Hard (3)
- "Greater / less" feedback after each guess
- Up to 3 hints, each narrowing the range (±10, ±5, ±3)
- Timer for each round
- Highscore per difficulty, saved in `highscore.txt`
- Input validation and play-again loop

## Build and run

Requires a C++17 compiler (g++ or clang++) and `make`.

```bash
git clone https://github.com/joelng25/Number-Guessing-Game-CLI.git
cd Number-Guessing-Game-CLI
make
./random-number
```

Run the tests:

```bash
make test
```

## Example

```text
Welcome to the Number Guessing Game!
I'm thinking of a number between 1 and 100.

Please select the difficulty level:
1. Easy (10 chances)
2. Medium (5 chances)
3. Hard (3 chances)

Enter your choice: 2

Great! You have selected the Medium difficulty level.
Let's start the game!

Enter your guess: 50
Incorrect! The number is less than 50.
You have 4 attempts left.

Do you want a hint? (Y/N): y

The number is between 27 and 47.
Enter your guess: 37
Congratulations! You guessed the correct number in 2 attempts.
```

## Project structure

- `game.h` — game rules (difficulty, hints, highscores), no input/output, unit tested
- `main.cc` — terminal input/output and game loop
- `tests/test_game.cc` — tests for the rules
