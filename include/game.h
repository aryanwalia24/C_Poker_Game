#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"
#include "poker_hand.h"

// Constants
#define START_MONEY 1000
#define SMALL_BLIND 10
#define BIG_BLIND 20
#define MAX_PLAYERS 10
#define INITIAL_POT 200

// Function prototypes
void initializeGame(Player players[], int *playerCount, Deck *deck);
void startGame(Player players[], int *playerCount, Deck *deck);
void playRound(Player players[], int playerCount, Deck *deck);
int displayMenu();

void setBlinds(Player players[], int playerCount);
void dealCards(Player players[], int playerCount, Deck *deck);
void executeBettingRound(Player players[], int playerCount, const Card communityCards[], int *pot);
void handleFlop(Deck *deck, Card communityCards[]);
void handleTurn(Deck *deck, Card communityCards[]);
void handleRiver(Deck *deck, Card communityCards[]);
void determineWinner(Player players[], int playerCount, const Card communityCards[], int *pot);
void displayPlayerCards(const Player *player, int display);
void displayCommunityCards(const Card communityCards[], int numCards);

#endif // GAME_H