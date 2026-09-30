#include "game.hpp"

#include <iostream>
#include <random>
#include <sstream>
#include <string>

namespace {

bool parseMenuChoice(const std::string& input, int& choice) {
  std::istringstream stream(input);
  char extraCharacter = '\0';

  return (stream >> choice) && !(stream >> extraCharacter);
}

void printMenu() {
  std::cout << "\nRock, Paper, Scissors, Lizard, Spock\n"
            << "1. Rock\n"
            << "2. Paper\n"
            << "3. Scissors\n"
            << "4. Lizard\n"
            << "5. Spock\n"
            << "0. Quit\n"
            << "Choose a gesture (0-5): ";
}

void printScore(int playerScore, int computerScore, bool finalScore) {
  const char* label = finalScore ? "Final score - You: " : "Score - You: ";
  std::cout << label << playerScore << " | Computer: " << computerScore << '\n';
}

}  // namespace

int main() {
  int playerScore = 0;
  int computerScore = 0;
  std::mt19937 engine(std::random_device{}());
  std::string input;

  while (true) {
    printMenu();
    if (!std::getline(std::cin, input)) {
      break;
    }

    int choice = 0;
    if (!parseMenuChoice(input, choice) || choice < 0 || choice > 5) {
      std::cout << "Invalid choice. Enter a number from 0 to 5.\n";
      continue;
    }

    if (choice == 0) {
      break;
    }

    const Gesture playerChoice = static_cast<Gesture>(choice - 1);
    const Gesture computerChoice = randomGesture(engine);
    const RoundResult result = resolveRound(playerChoice, computerChoice);

    std::cout << "You chose: " << gestureName(playerChoice) << '\n'
              << "Computer chose: " << gestureName(computerChoice) << '\n';

    if (result == RoundResult::Tie) {
      std::cout << "It's a tie.\n";
    } else if (result == RoundResult::PlayerWin) {
      ++playerScore;
      std::cout << winningRule(playerChoice, computerChoice) << " You win!\n";
    } else {
      ++computerScore;
      std::cout << winningRule(computerChoice, playerChoice) << " Computer wins!\n";
    }

    printScore(playerScore, computerScore, false);
  }

  printScore(playerScore, computerScore, true);
  return 0;
}
