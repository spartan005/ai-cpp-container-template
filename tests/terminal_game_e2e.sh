#!/bin/bash

set -euo pipefail

game_path="${1:-build/app}"

play_output="$(printf 'hello\n9\n1\n0\n' | "$game_path")"
invalid_count="$(printf '%s\n' "$play_output" | grep -Fc 'Invalid choice. Enter a number from 0 to 5.')"

if [[ "$invalid_count" -ne 2 ]]; then
  echo "Expected invalid input to be rejected twice."
  exit 1
fi

for expected_text in 'You chose: Rock' 'Computer chose:' 'Score - You:' \
                     'Final score - You:'; do
  if ! printf '%s\n' "$play_output" | grep -Fq "$expected_text"; then
    echo "Missing expected output: $expected_text"
    exit 1
  fi
done

eof_output="$(printf '' | "$game_path")"
if ! printf '%s\n' "$eof_output" | grep -Fq 'Final score - You:'; then
  echo "Expected EOF to print the final score."
  exit 1
fi

echo "Terminal game E2E tests passed."
