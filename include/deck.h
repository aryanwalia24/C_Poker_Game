#ifndef DECK_H
#define DECK_H

#include "card.h"

#define NUM_CARDS 52

typedef struct
{
    Card cards[NUM_CARDS]; // Storing all cards
    int inplay[NUM_CARDS]; // currently used or not b/w 1 and 0
    int top;               // next card to draw (index)
} Deck;

// Prototypes
void initialiseDeck(Deck *deck);
void shuffleDeck(Deck *deck);
Card drawCard(Deck *deck);

#endif DECK_H