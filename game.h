#pragma once

#include <algorithm>
#include <array>
#include <limits>
#include <string>
#include <utility>

namespace game {

constexpr int MIN_NUM = 1;
constexpr int MAX_NUM = 100;
constexpr int MAX_HINTS = 3;
constexpr int NO_SCORE = std::numeric_limits<int>::max();

enum class Difficulty { Easy = 1, Medium = 2, Hard = 3 };

using Highscores = std::array<int, 3>;

inline int attemptsFor(Difficulty d) {
  switch (d) {
    case Difficulty::Easy:
      return 10;
    case Difficulty::Hard:
      return 3;
    case Difficulty::Medium:
    default:
      return 5;
  }
}

inline std::string nameOf(Difficulty d) {
  switch (d) {
    case Difficulty::Easy:
      return "Easy";
    case Difficulty::Hard:
      return "Hard";
    case Difficulty::Medium:
    default:
      return "Medium";
  }
}

// Each hint narrows the range around the answer: +-10, then +-5, then +-3.
inline std::pair<int, int> hintRange(int answer, int hint_level) {
  static constexpr std::array<int, MAX_HINTS> widths = {10, 5, 3};
  int width = widths[std::clamp(hint_level, 0, MAX_HINTS - 1)];
  return {std::max(MIN_NUM, answer - width), std::min(MAX_NUM, answer + width)};
}

// Returns true when `attempts` beats the stored score for that difficulty.
inline bool updateHighscore(Highscores& scores, Difficulty d, int attempts) {
  int& best = scores[static_cast<int>(d) - 1];
  if (attempts < best) {
    best = attempts;
    return true;
  }
  return false;
}

}  // namespace game
