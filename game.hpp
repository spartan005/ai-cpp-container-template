#ifndef GAME_HPP
#define GAME_HPP

#include <random>
#include <string_view>

enum class Gesture { Rock, Paper, Scissors, Lizard, Spock };

enum class RoundResult { PlayerWin, ComputerWin, Tie };

RoundResult resolveRound(Gesture player, Gesture computer);
std::string_view gestureName(Gesture gesture);
std::string_view winningRule(Gesture winner, Gesture loser);
Gesture randomGesture(std::mt19937& engine);

#endif
