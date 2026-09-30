# Spec: Terminal Rock, Paper, Scissors, Lizard, Spock

## Objective

Build a self-contained C++17 terminal game for one human player against a
computer that chooses among five gestures at random. The player can repeatedly
play rounds, view the result and running score, and quit at any time.

## Rules

- Scissors cuts Paper.
- Paper covers Rock.
- Rock crushes Lizard.
- Lizard poisons Spock.
- Spock smashes Scissors.
- Scissors decapitates Lizard.
- Lizard eats Paper.
- Paper disproves Spock.
- Spock vaporizes Rock.
- Rock crushes Scissors.

## Terminal Behavior

- Choices `1` through `5` select Rock, Paper, Scissors, Lizard, and Spock.
- Choice `0` exits the session.
- Invalid, malformed, and out-of-range input is rejected without changing the
  score.
- EOF exits cleanly and prints the final score.
- Each valid round displays both gestures, the winning rule or tie result, and
  the running score.

## Architecture

- `game.hpp` exposes typed gestures, round outcomes, rule-text lookup, and
  random-choice functions.
- `game.cpp` contains one canonical table of winning relationships.
- `main.cpp` owns terminal input/output and session scores.

## Validation

Run the full automated suite with:

```bash
./test_runner.sh
```

The unit tests cover every possible gesture pairing. The shell E2E test covers
invalid input recovery, a played round, quitting, and EOF.
