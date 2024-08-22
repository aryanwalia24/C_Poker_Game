# Poker Implementation in C

## Project Description
For this project, I decided to build a 🎲 `Texas Hold'em Poker game from scratch using C`. The goal was to put into practice the programming concepts I've picked up during my classes and create something that's both functional and showcases my skills.

#### Here's what I focused on:
- 🃏 **Card Representation**: Bitwise operations to represent cards. Storage and manipulation of card data.
- ♠️ **Game Mechanics**: Handling all core parts of Texas Hold'em, including dealing cards, managing bets, and evaluating winners based on poker hand rankings.
- 🔧 **Modular Code**: Organized into modules. Card & player management, game logic, and actions are handled separately.

The end result is a complete poker game that not only works well but also demonstrates a solid grasp of programming principles and game development. The modular code structure makes it understandable for all developers.

## Project Proposal - Idea Selection

I chose to implement a game rather than a flashy project. This decision integrates key programming concepts learned from our classes, including bitwise operations, modular structure, and code conventions. I brainstormed on how to implement what I've studied with this project before finalizing the idea. I aimed to make it implementation-intensive rather than just concept-heavy. This project allowed me to apply what I've learned and demonstrate both my understanding and ability to solve complex problems creatively and critically.

## Goals

- 🎮 **Two-Player Game**: Implement a complete Texas Hold'em poker game for 2 players.
- 🛠️ **Player Management**: Handle player actions such as betting and tracking wallets.
- 📜 **Game Logic**: Develop core game logic for dealing cards and managing betting rounds.
- 🏆 **Hand Evaluation**: Implement algorithms to determine the winning hand.
- 📚 **Static Library**: Build a `lib.a` static library for core functionalities.

# Structure and Design
```
C_POKER_GAME/
├── include/
│ ├── card.h
│ ├── deck.h
│ └── ...etc
├── src/
│ ├── card.c
│ ├── deck.c
│ └── ...etc
├── headerLibrary/
│ └── lib.a
├── .gitignore
└── README.md
```



## Texas Hold'em Summary

- 🎲 **Game Overview**: Texas Hold'em is a popular poker variant.
- 🃏 **Hole Cards**: Each player is dealt two private cards, known as "hole cards."
- 🃏 **Community Cards**: Five community cards are dealt to form the best possible five-card hand.
- 💵 **Betting Rounds**:
  - Players can **check**, **bet**, **raise**, or **fold** based on their hand and strategy.
- 🃏 **Community Cards Stages**:
  - **Flop**: Three cards dealt.
  - **Turn**: One card dealt.
  - **River**: One card dealt.
- 🏆 **Objective**: Create the highest-ranking hand by combining hole cards and community cards.
- 🏅 **Winning**: The player with the best hand at the end of the betting rounds wins the pot.


