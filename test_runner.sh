#!/bin/bash

set -euo pipefail

mkdir -p build

g++ -std=c++17 -Wall -Wextra -pedantic game.cpp tests/game_test.cpp -I. \
  -o build/game_tests
build/game_tests

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp game.cpp -o build/app
bash tests/terminal_game_e2e.sh build/app
