#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/deck.h"

typedef unsigned int ut; //

// func1 - intilising the deck at start of the game
void initialiseDeck(Deck *deck)
{
    // 52 cards deck - Texas Hold'em variant
    int idx = 0;
    for (ut suit = 0; suit < 4; suit++)
    {
        for (ut val = 1; val <= 13; val++)
        {
            deck->cards[idx] = (suit << VALUE_BITS) | val; // storing int bits (2 suit bits - 4 value bits)
            deck->inplay[idx] = 0;                         // starting all cards are set 0 (not in play rn)
            idx++;
        }
    }
    deck->top = 0;
}

// shuffle function
void shuffleDeck(Deck *deck)
{
    srand(time(NULL)); // for random no.

    // Algo -> swapping with random index
    for (int i = NUM_CARDS - 1; i >= 1; i--)
    {
        // this is called Fisher-Yates algo for shuffling
        int j = rand() % (i + 1); // idx within range [0,i]
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

// Drawing the next card
Card drawCard(Deck *deck)
{
    if (deck->top >= NUM_CARDS)
    {
        printf("All cards have been drawn.\n");
        return 0;
    }

    Card currCard = deck->cards[deck->top];
    deck->inplay[deck->top] = 1; // marking drawn card
    deck->top++;

    return currCard;
}