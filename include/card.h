#ifndef CARD_H
#define CARD_H

#include <stdio.h> 
#include <ctype.h> 

#define VALUE_BITS 4
#define VALUE_MASK 0xF
// Mask 15 - 0000 1111
// ((1 << VAL_BITS) - 1)

#define SUIT_BITS 2
#define SUIT_MASK 0x30
// Mask 48 - 0011 0000
// (((1 << SUIT_BITS) - 1) << 4)

typedef unsigned int Card; // positive values & expected bitwise operations

void parseCardInput(void *input, int format, Card *card);
unsigned int getCardValue(Card card);
unsigned int getCardSuit(Card card);
void printCard(Card card);

char mapNumberToSuit(unsigned int suitNum);
unsigned int mapSuitToNumber(char suit);

#endif // CARD_H
