#include <cassert>
#include <iostream>

#include "../game.h"

using namespace game;

int main() {
  assert(attemptsFor(Difficulty::Easy) == 10);
  assert(attemptsFor(Difficulty::Medium) == 5);
  assert(attemptsFor(Difficulty::Hard) == 3);

  assert(hintRange(50, 0) == std::make_pair(40, 60));
  assert(hintRange(50, 1) == std::make_pair(45, 55));
  assert(hintRange(50, 2) == std::make_pair(47, 53));
  assert(hintRange(2, 0) == std::make_pair(1, 12));     // clamped to MIN_NUM
  assert(hintRange(99, 0) == std::make_pair(89, 100));  // clamped to MAX_NUM

  Highscores scores;
  scores.fill(NO_SCORE);
  assert(updateHighscore(scores, Difficulty::Hard, 3));
  assert(scores[2] == 3);
  assert(!updateHighscore(scores, Difficulty::Hard, 3));
  assert(updateHighscore(scores, Difficulty::Hard, 2));
  assert(scores[0] == NO_SCORE);

  std::cout << "All tests passed" << std::endl;
  return 0;
}
