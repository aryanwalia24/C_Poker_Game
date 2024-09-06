#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"
#include "poker_hand.h"

// Game Constants
#define START_MONEY 1000
#define SMALL_BLIND 10
#define BIG_BLIND 20
#define MAX_PLAYERS 10
#define INITIAL_POT 200

// Game Flow Functions
void initializeGame(Player **players, int *playerCount, Deck *deck);
void startGame(Player **players, int *playerCount, Deck *deck);
void playRound(Player *players, int playerCount, Deck *deck);
int displayMenu();

// Game Helper Functions
void setBlinds(Player *players, int playerCount);
void dealCards(Player *players, int playerCount, Deck *deck);
void handleFlop(Deck *deck, Card communityCards[]);
void handleTurn(Deck *deck, Card communityCards[]);
void handleRiver(Deck *deck, Card communityCards[]);
void executeBettingRound(Player *players, int playerCount, const Card communityCards[], int *pot);
void determineWinner(Player *players, int playerCount, const Card communityCards[], int *pot);

// Utility Functions
void displayPlayerCards(const Player *player, int display);
void displayCommunityCards(const Card communityCards[], int numCards);
void superCleanup(Player *players, int playerCount);
void burnCard(Deck *deck);

#endif // GAME_H