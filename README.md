# 🃏 Texas Hold'em Poker in C 

![image](https://github.com/user-attachments/assets/52fac160-155e-44e9-b86a-6ca8e4d28ce1)

---

## Table of Contents

1. [Project Overview](#-project-overview)
2. [Project Proposal](#-project-proposal)
3. [Goals](#-goals)
4. [Structure and Design](#-structure-and-design)
5. [Texas Hold&#39;em Summary](#️-texas-holdem-summary)

---

## 📜 Project Overview

I created a **🎲 `Texas Hold'em Poker Game`** using C to demonstrate my programming skills and understanding of game development. This project integrates various programming concepts, including bitwise operations, modular code design, and game mechanics, resulting in a fully functional poker game.

### 🔍 Focus Areas:

* **🃏 Card Representation** : Efficient use of bitwise operations for card data storage and manipulation.
* **♠️ Game Mechanics** : Comprehensive implementation of Texas Hold'em rules, including dealing, betting, and hand evaluation.
* **🔧 Modular Code** : A clean and organized codebase with separate modules for card handling, player management, and game logic.

This project showcases my ability to apply programming principles creatively and effectively, resulting in a robust and engaging game.

---

## 💡 Project Proposal

I opted to implement a game rather than a purely conceptual project to put into practice the key programming concepts learned in class. The focus was on implementation, ensuring that each aspect of the game was both functional and modular. This approach allowed me to demonstrate not only my understanding of the material but also my ability to solve complex problems in a creative and systematic manner.

---

## 🏆 Goals

* **🎮 Two-Player Game** : Create a complete Texas Hold'em poker experience for 2 players.
* **🛠️ Player Management** : Implement robust player actions, including betting and wallet management.
* **📜 Game Logic** : Develop the core mechanics for dealing cards and conducting betting rounds.
* **🏅 Hand Evaluation** : Create algorithms to accurately determine the winning hand.
* **📚 Static Library** : Compile core functionalities into a reusable `libpoker.a` static library.

---

## 📂 Structure and Design

```
C_POKER_GAME/
├── include/
│   ├── card.h
│   ├── deck.h
│   ├── game.h
│   ├── player.h
│   └── poker_hand.h
├── src/
│   ├── card.c
│   ├── deck.c
│   ├── game.c
│   ├── player.c
│   └── poker_hand.c
├── libpoker.a
├── commands.txt
├── main.c
├── .gitignore
├── run_project.sh
└── README.md
```

---

## Getting Started

### Prerequisites

- **GCC Compiler**: Ensure you have the GCC compiler installed on your system.

### Cloning the Repository

1. Clone the repository from GitHub:
    ```
    git clone https://github.com/aryanwalia24/C_Poker_Game.git  
    ```
2. Navigate into the project directory:
    ```
    cd C_POKER_GAME
    ```

### Compilation

#### For Unix based Systems 
1. To compile the project, use the provided run_project.sh script:
    ```
    ./run_project.sh
    ```
 **_-> Check run_project.sh file for all background commands_**
 
#### For Windows
1. To compile the project, either use commands in `commands.txt` or
    ```
    gcc -I./include main.c -L. -lpoker -o poker_game
    ```
### Running the Program

1. After successful compilation, you can run the program using:
    ``` 
    ./poker_game
    ```
---

## ♠️ Texas Hold'em Summary

* **🎲 Game Overview** : Texas Hold'em is one of the most popular poker variants.
* **🃏 Hole Cards** : Each player receives two private "hole cards."
* **🃏 Community Cards** : Five community cards are revealed throughout the game to form the best possible hand.
* **💵 Betting Rounds** :
  * Players can **check**, **bet**, **raise**, or **fold** based on their hand and strategy.
* **🃏 Community Cards Stages** :
  * **Flop** : The first three community cards.
  * **Turn** : The fourth community card.
  * **River** : The fifth and final community card.
* **🏆 Objective** : Create the highest-ranking hand using a combination of hole cards and community cards.
* **🥇 Winning** : The player with the best hand at the end of the betting rounds wins the pot.
---

# Gameplay
video area
