#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"
#include "poker_hand.h"

// Constants
#define START_MONEY 1000
#define SMALL_BLIND 10
#define BIG_BLIND 20

// Function prototypes
void initializeGame(Player players[], int *playerCount, Deck *deck);
void startGame(Player players[], int *playerCount, Deck *deck);
void playRound(Player players[], int playerCount, Deck *deck);
int displayMenu();

void setBlinds(Player players[], int playerCount);
void dealCards(Player players[], int playerCount, Deck *deck);
void executeBettingRound(Player players[], int playerCount);
void handleFlop(Deck *deck);
void handleTurn(Deck *deck);
void handleRiver(Deck *deck);
void determineWinner(Player players[], int playerCount);
void displayPlayerCards(const Player *player, int display);
void displayCommunityCards(const Card communityCards[], int numCards);

#endif // GAME_H
