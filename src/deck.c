#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/deck.h"

void initialiseDeck(Deck *deck)
{
    deck->cards = (Card *)malloc(NUM_CARDS * sizeof(Card));
    deck->inplay = (int *)malloc(NUM_CARDS * sizeof(int));
    if (deck->cards == NULL || deck->inplay == NULL)
    {
        fprintf(stderr, "Memory allocation failed for deck.\n");
        exit(EXIT_FAILURE);
    }

    int idx = 0;
    for (unsigned int suit = 0; suit < 4; suit++)
    {
        for (unsigned int val = 1; val <= 13; val++)
        {
            deck->cards[idx] = (suit << VALUE_BITS) | val;
            deck->inplay[idx] = 0;
            idx++;
        }
    }
    deck->top = 0;
}

// fisher-yates algorithm
void shuffleDeck(Deck *deck)
{
    srand((unsigned int)time(NULL));

    for (int i = NUM_CARDS - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1); // Random index range [0, i]
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

Card drawCard(Deck *deck)
{
    if (deck->top >= NUM_CARDS)
    {
        printf("All cards have been drawn.\n");
        return 0;
    }

    Card currCard = deck->cards[deck->top];
    deck->inplay[deck->top] = 1;
    deck->top++;

    return currCard;
}

void cleanupDeck(Deck *deck)
{
    free(deck->cards);
    free(deck->inplay);
}