#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/card.h"

char mapNumberToSuit(unsigned int suitNum)
{
   switch (suitNum)
   {
   case 0:
      return 'H'; // H
   case 1:
      return 'D'; // D
   case 2:
      return 'C'; // C
   case 3:
      return 'S'; // S
   default:
      return 'H'; // Invalid input 'H'
   }
}

unsigned int mapSuitToNumber(char suit)
{
   switch (suit)
   {
   case 'H':
      return 0; // H
   case 'D':
      return 1; // D
   case 'C':
      return 2; // C
   case 'S':
      return 3; // S
   default:
      return 0; // Invalid input 0
   }
}

void parseCardInput(void *input, int format, Card *card)
{
   if (format == 1)
   {
      // format 1 : (CHAR)(INT)
      // ex ; String -> "H4","S1"
      char *str = (char *)input;
      if (strlen(str) < 2 || strlen(str) > 3) // len range 2,3 (H4 or D13)
      {
         printf("Invalid card format. The string must be between 2 or 3 characters length.\n");
         return;
      }

      char suit = str[0];
      unsigned int value = (unsigned int)atoi(str + 1); // or (str+1) = str[1]

      // Errorschecker {
      if (value < 1 || value > 13)
      {
         printf("Invalid card value. Please enter a value between 1 and 13.\n");
         return;
      }

      if (strchr("HDCS", suit) == NULL)
      {
         printf("Invalid suit. Please enter 'H', 'D', 'C', or 'S'.\n");
         return;
      }
      // }

      // getting suit number -> left shifting 4 times and -> add cardValue
      *card = (mapSuitToNumber(suit) << VALUE_BITS) | (value & VALUE_BITS);
   }
   else if (format == 2)
   {
      // format 2 : (suitNum) (Value)
      // 1 - H , 2 - D, 3 - C, 4 - S
      // 1 - 13 (Ace to Kings)
      // ex : String -> "1 4" -> 4 of Hearts

      char *str = (char *)input;
      unsigned int suitNum, value;
      // Errorschecker {
      if (sscanf(str, "%u %u", &suitNum, &value) != 2) // returns number of space seperated parts
      {
         printf("Invalid input format. Expected format: 'suitNum value'.\n");
         return;
      }

      if (suitNum < 1 || suitNum > 4 || value < 1 || value > 13)
      {
         printf("Invalid suit number or card value. Suit number must be 1-4 and value must be 1-13.\n");
         return;
      }
      // }

      // left shifting suit Num 4 times and -> add cardValue
      // suitNum-1 to convert 1-4 range to 0-3 for bit manipulation
      *card = ((suitNum - 1) << VALUE_BITS) | (value & VALUE_MASK);
   }
   else
   {
      printf("Invalid format. Supported formats are 1.(Char)(INT) and 2.(suitNum) (Value)\n");
   }
}

unsigned int getCardValue(Card card)
{
   return (card & VALUE_MASK);
}

unsigned int getCardSuit(Card card)
{
   return (card & SUIT_MASK) >> VALUE_BITS;
}

void printCard(Card card)
{
   static const char *faceStrings[] = {
       "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
   static const char *suitStrings[] = {
       "Hearts", "Spades", "Clubs", "Diamonds"};

   unsigned int value = getCardValue(card);
   unsigned int suit = getCardSuit(card);
   char suitChar = mapNumberToSuit(suit);

   if (value > 0 && value <= 13 && suit > 0 && suit <= 4)
   {
      printf("%s of %s\n", faceStrings[value - 1], suitStrings[suit - 1]);
   }
   else
   {
      printf("Invalid card\n");
   }
}
