#include "game.hpp"

#include <cassert>
#include <iostream>
#include <random>
#include <string_view>

namespace {

void expectRound(Gesture player, Gesture computer, RoundResult expectedResult,
                 std::string_view expectedRule = {}) {
  assert(resolveRound(player, computer) == expectedResult);

  if (!expectedRule.empty()) {
    assert(winningRule(player, computer) == expectedRule);
  }
}

void testWinningRules() {
  expectRound(Gesture::Scissors, Gesture::Paper, RoundResult::PlayerWin,
              "Scissors cuts Paper.");
  expectRound(Gesture::Paper, Gesture::Rock, RoundResult::PlayerWin,
              "Paper covers Rock.");
  expectRound(Gesture::Rock, Gesture::Lizard, RoundResult::PlayerWin,
              "Rock crushes Lizard.");
  expectRound(Gesture::Lizard, Gesture::Spock, RoundResult::PlayerWin,
              "Lizard poisons Spock.");
  expectRound(Gesture::Spock, Gesture::Scissors, RoundResult::PlayerWin,
              "Spock smashes Scissors.");
  expectRound(Gesture::Scissors, Gesture::Lizard, RoundResult::PlayerWin,
              "Scissors decapitates Lizard.");
  expectRound(Gesture::Lizard, Gesture::Paper, RoundResult::PlayerWin,
              "Lizard eats Paper.");
  expectRound(Gesture::Paper, Gesture::Spock, RoundResult::PlayerWin,
              "Paper disproves Spock.");
  expectRound(Gesture::Spock, Gesture::Rock, RoundResult::PlayerWin,
              "Spock vaporizes Rock.");
  expectRound(Gesture::Rock, Gesture::Scissors, RoundResult::PlayerWin,
              "Rock crushes Scissors.");
}

void testReversedRulesAndTies() {
  const Gesture gestures[] = {Gesture::Rock, Gesture::Paper, Gesture::Scissors,
                              Gesture::Lizard, Gesture::Spock};

  for (Gesture gesture : gestures) {
    assert(resolveRound(gesture, gesture) == RoundResult::Tie);
  }

  assert(resolveRound(Gesture::Paper, Gesture::Scissors) == RoundResult::ComputerWin);
  assert(resolveRound(Gesture::Rock, Gesture::Paper) == RoundResult::ComputerWin);
  assert(resolveRound(Gesture::Lizard, Gesture::Rock) == RoundResult::ComputerWin);
  assert(resolveRound(Gesture::Spock, Gesture::Lizard) == RoundResult::ComputerWin);
  assert(resolveRound(Gesture::Scissors, Gesture::Spock) == RoundResult::ComputerWin);
  assert(resolveRound(Gesture::Lizard, Gesture::Scissors) == RoundResult::ComputerWin);
  assert(resolveRound(Gesture::Paper, Gesture::Lizard) == RoundResult::ComputerWin);
  assert(resolveRound(Gesture::Spock, Gesture::Paper) == RoundResult::ComputerWin);
  assert(resolveRound(Gesture::Rock, Gesture::Spock) == RoundResult::ComputerWin);
  assert(resolveRound(Gesture::Scissors, Gesture::Rock) == RoundResult::ComputerWin);
}

void testNamesAndRandomChoices() {
  assert(gestureName(Gesture::Rock) == "Rock");
  assert(gestureName(Gesture::Paper) == "Paper");
  assert(gestureName(Gesture::Scissors) == "Scissors");
  assert(gestureName(Gesture::Lizard) == "Lizard");
  assert(gestureName(Gesture::Spock) == "Spock");

  std::mt19937 engine(1234);
  for (int index = 0; index < 100; ++index) {
    const Gesture choice = randomGesture(engine);
    assert(choice == Gesture::Rock || choice == Gesture::Paper ||
           choice == Gesture::Scissors || choice == Gesture::Lizard ||
           choice == Gesture::Spock);
  }
}

}  // namespace

int main() {
  testWinningRules();
  testReversedRulesAndTies();
  testNamesAndRandomChoices();
  std::cout << "All game tests passed.\n";
  return 0;
}
