#!/bin/bash

# Compiling source files
gcc -I./include -c src/card.c -o src/card.o
gcc -I./include -c src/deck.c -o src/deck.o
gcc -I./include -c src/game.c -o src/game.o
gcc -I./include -c src/player.c -o src/player.o
gcc -I./include -c src/poker_hand.c -o src/poker_hand.o

# Static library
ar rcs libpoker.a src/card.o src/deck.o src/game.o src/player.o src/poker_hand.o

# Compile main file and link with static library
gcc -I./include main.c -L. -lpoker -o poker_game

if [ $? -eq 0 ]; then
    echo "Compilation successful"
    echo "./poker_game to run the program"
else 
    echo "Compilation failed"
fi
