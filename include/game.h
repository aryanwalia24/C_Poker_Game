#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"
#include "poker_hand.h"

// Constants
#define MAX_PLAYERS 10
#define MAX_NAME_LENGTH 50
#define START_MONEY 1000
#define SMALL_BLIND 10
#define BIG_BLIND 20

// Function prototypes
void initializeGame(Player players[], int *numPlayers, Deck *deck);
void startGame(Player players[], int numPlayers, Deck *deck);
void playRound(Player players[], int numPlayers, Deck *deck);
int displayMenu();

void setBlinds(Player players[], int numPlayers);
void dealCards(Player players[], int numPlayers, Deck *deck);
void executeBettingRound(Player players[], int numPlayers);
void handleFlop(Deck *deck);
void handleTurn(Deck *deck);
void handleRiver(Deck *deck);
void determineWinner(Player players[], int numPlayers);

#endif // GAME_H
