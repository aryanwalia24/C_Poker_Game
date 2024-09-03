#ifndef POKER_HAND_H
#define POKER_HAND_H

#include "card.h"

#define MAX_CARDS 5

typedef enum
{
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
} PokerHandRank;

typedef struct
{
    PokerHandRank rank;
    Card cards[MAX_CARDS];
} PokerHand;

PokerHand *createPokerHand();
void evaluatePokerHand(Card playerCards[], const Card communityCards[], PokerHand *optimalHand);
int comparePokerHands(const PokerHand *hand1, const PokerHand *hand2);
const char *pokerHandToString(int rank);
// void freePokerHand(PokerHand *hand);
// void cleanupPokerHands(PokerHand *hands, int numHands);

#endif // POKER_HAND_H