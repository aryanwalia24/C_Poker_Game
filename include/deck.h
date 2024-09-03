#ifndef DECK_H
#define DECK_H

#include "card.h"

#define NUM_CARDS 52

typedef struct
{
    Card *cards; // Storing all cards
    int *inplay; // currently used or not b/w 1 and 0
    int top;     // next card to draw (index)
} Deck;

void initialiseDeck(Deck *deck);
void shuffleDeck(Deck *deck);
Card drawCard(Deck *deck);
void cleanupDeck(Deck *deck); 

#endif // DECK_H