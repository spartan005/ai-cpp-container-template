#include "game.hpp"

#include <array>

namespace {

struct WinningRule {
  Gesture winner;
  Gesture loser;
  std::string_view description;
};

constexpr std::array<WinningRule, 10> kWinningRules{{
    {Gesture::Scissors, Gesture::Paper, "Scissors cuts Paper."},
    {Gesture::Paper, Gesture::Rock, "Paper covers Rock."},
    {Gesture::Rock, Gesture::Lizard, "Rock crushes Lizard."},
    {Gesture::Lizard, Gesture::Spock, "Lizard poisons Spock."},
    {Gesture::Spock, Gesture::Scissors, "Spock smashes Scissors."},
    {Gesture::Scissors, Gesture::Lizard, "Scissors decapitates Lizard."},
    {Gesture::Lizard, Gesture::Paper, "Lizard eats Paper."},
    {Gesture::Paper, Gesture::Spock, "Paper disproves Spock."},
    {Gesture::Spock, Gesture::Rock, "Spock vaporizes Rock."},
    {Gesture::Rock, Gesture::Scissors, "Rock crushes Scissors."},
}};

const WinningRule* findWinningRule(Gesture winner, Gesture loser) {
  for (const WinningRule& rule : kWinningRules) {
    if (rule.winner == winner && rule.loser == loser) {
      return &rule;
    }
  }
  return nullptr;
}

}  // namespace

RoundResult resolveRound(Gesture player, Gesture computer) {
  if (player == computer) {
    return RoundResult::Tie;
  }
  return findWinningRule(player, computer) != nullptr ? RoundResult::PlayerWin
                                                       : RoundResult::ComputerWin;
}

std::string_view gestureName(Gesture gesture) {
  switch (gesture) {
    case Gesture::Rock:
      return "Rock";
    case Gesture::Paper:
      return "Paper";
    case Gesture::Scissors:
      return "Scissors";
    case Gesture::Lizard:
      return "Lizard";
    case Gesture::Spock:
      return "Spock";
  }
  return "";
}

std::string_view winningRule(Gesture winner, Gesture loser) {
  const WinningRule* rule = findWinningRule(winner, loser);
  return rule == nullptr ? "" : rule->description;
}

Gesture randomGesture(std::mt19937& engine) {
  std::uniform_int_distribution<int> distribution(0, 4);
  return static_cast<Gesture>(distribution(engine));
}
