#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define HAND_SIZE 2 

typedef struct
{
    int id;
    char name[MAX_NAME_LENGTH];
    int wallet;
    Card hand[HAND_SIZE];
} Player;

int createPlayer(int id, char *name, int startMoney, Player *player);
int updateWallet(Player *player, int amount);
int getWallet(const Player *player, int *balance);
void displayPlayer(const Player *player);

#endif // PLAYER_H
