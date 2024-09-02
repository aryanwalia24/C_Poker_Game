#include "../include/game.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int getValidIntGame(int min, int max, const char *prompt);
static int getValidBet(int wallet, const char *prompt);

void initializeGame(Player players[], int *playerCount, Deck *deck)
{
    printf("\nEnter the number of players (minimum 2): ");
    *playerCount = 2;

    printf("\nEnter player names:\n");
    for (int i = 0; i < *playerCount; i++)
    {
        printf("Enter name for player %d: ", i + 1);
        if (fgets(players[i].name, MAX_NAME_LENGTH, stdin) != NULL)
        {
            size_t len = strlen(players[i].name);
            if (len > 0 && players[i].name[len - 1] == '\n')
            {
                players[i].name[len - 1] = '\0';
            }
            createPlayer(i + 1, players[i].name, START_MONEY, &players[i]);
        }
        else
        {
            fprintf(stderr, "Error reading player name.\n");
            exit(EXIT_FAILURE);
        }
    }

    initialiseDeck(deck);
    shuffleDeck(deck);
}

void startGame(Player players[], int *playerCount, Deck *deck)
{
    int continueGame = 1;

    while (continueGame)
    {
        continueGame = displayMenu();
        if (continueGame)
        {
            initializeGame(players, playerCount, deck);
            playRound(players, *playerCount, deck);
        }
    }
    printf("\n---------- Game over. Thanks for playing Poker! ----------\n");
}

void playRound(Player players[], int numPlayers, Deck *deck)
{
    printf("\n--------------- Starting A New Round -------------\n");
    printf("1. Setting Blinds \n\n");

    printf("---------------------- Blinds ------------------------\n");
    setBlinds(players, numPlayers);

    printf("\n-------------- Dealing Cards to Players ------------\n");
    dealCards(players, numPlayers, deck);

    executeBettingRound(players, numPlayers);

    printf("\n-------------- Revealing The FLOP -------------------\n");
    handleFlop(deck);
    executeBettingRound(players, numPlayers);

    printf("\n-------------- Revealing The TURN -------------------\n");
    handleTurn(deck);
    executeBettingRound(players, numPlayers);

    printf("\n-------------- Revealing The RIVER -------------------\n");
    handleRiver(deck);
    executeBettingRound(players, numPlayers);

    determineWinner(players, numPlayers);
}

int displayMenu()
{
    int choice;
    while (1)
    {
        printf("\n------------------ Texas Hold'em Poker -------------\n\n");
        printf("1. Start a new round\n");
        printf("2. Exit game\n\n");
        printf("Choose an option: ");

        choice = getValidIntGame(1, 2, "");

        if (choice == 1)
        {
            return 1; // Start a new round
        }
        else if (choice == 2)
        {
            return 0; // Exit game
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void setBlinds(Player players[], int numPlayers)
{
    if (numPlayers < 2)
    {
        printf("Not enough players to set blinds.\n");
        return;
    }
    printf("%s pays Small Blind: $%d\n", players[0].name, SMALL_BLIND);
    printf("%s pays Big Blind: $%d\n", players[1].name, BIG_BLIND);

    players[0].wallet -= SMALL_BLIND; 
    players[1].wallet -= BIG_BLIND;   
}

void dealCards(Player players[], int numPlayers, Deck *deck)
{
    if (numPlayers < 1)
    {
        printf("No players to deal cards to.\n");
        return;
    }

    printf("Dealing cards...\n");
    for (int i = 0; i < numPlayers; i++)
    {
        players[i].hand[0] = drawCard(deck);
        players[i].hand[1] = drawCard(deck);
    }
}

void displayPlayerCards(const Player *player, int display)
{
    if (display)
    {
        printf("%s's cards: ", player->name);
        printCard(player->hand[0]);
        printCard(player->hand[1]);
        printf("\n");
    }
    else
    {
        printf("Player's cards are hidden.\n");
    }
}

void displayCommunityCards(const Card communityCards[], int numCards)
{
    printf("Community cards: \n");
    for (int i = 0; i < numCards; i++)
    {
        if (communityCards[i] != 0)
        {
            printCard(communityCards[i]);
        }
        else
        {
            printf("Invalid card ");
        }
    }
    printf("\n");
}

void executeBettingRound(Player players[], int numPlayers)
{
    printf("\n------------ Betting Round ------------\n");
    for (int i = 0; i < numPlayers; i++)
    {
        printf("\n%s's turn:\n", players[i].name);
        int bet = getValidBet(players[i].wallet, "Enter bet amount (or 0 to check/fold): ");
        if (bet > 0)
        {
            players[i].wallet -= bet;
            printf("%s bets $%d.\n", players[i].name, bet);
        }
        else
        {
            printf("%s checks/folds.\n", players[i].name);
        }
    }
}

void handleFlop(Deck *deck)
{
    printf("\nRevealing the flop...\n");
    Card communityCards[3];
    for (int i = 0; i < 3; i++)
    {
        communityCards[i] = drawCard(deck);
    }
    displayCommunityCards(communityCards, 3);
}

void handleTurn(Deck *deck)
{
    printf("\nRevealing the turn...\n");
    Card communityCards[1];
    communityCards[0] = drawCard(deck);
    displayCommunityCards(communityCards, 1);
}

void handleRiver(Deck *deck)
{
    printf("\nRevealing the river...\n");
    Card communityCards[1];
    communityCards[0] = drawCard(deck);
    displayCommunityCards(communityCards, 1);
}

void determineWinner(Player players[], int numPlayers)
{
    if (numPlayers < 1)
    {
        printf("No players to determine a winner.\n");
        return;
    }

    Card communityCards[5];
    PokerHand bestHands[2];

    for (int i = 0; i < numPlayers; i++)
    {
        evaluatePokerHand(players[i].hand, communityCards, &bestHands[i]);
    }

    int winnerIndex = 0;
    for (int i = 1; i < numPlayers; i++)
    {
        if (comparePokerHands(&bestHands[i], &bestHands[winnerIndex]) > 0)
        {
            winnerIndex = i;
        }
    }

    const char *handType = pokerHandToString(bestHands[winnerIndex].rank);
    int amountWon = players[winnerIndex].wallet - START_MONEY;

    printf("\n------ The Winner is %s with %s and has won $%d! ------\n", players[winnerIndex].name, handType, amountWon);

    printf("\n-------------- Game Statistics -------------\n");
    for (int i = 0; i < numPlayers; i++)
    {
        printf("%s's winnings: $%d\n", players[i].name, players[i].wallet - START_MONEY);
        printf("%s's cards: ", players[i].name);
        printCard(players[i].hand[0]);
        printCard(players[i].hand[1]);
        printf("\n");
    }
    printf("\nRound complete.\n");
}

static int getValidIntGame(int min, int max, const char *prompt)
{
    int value;
    do
    {
        printf(prompt);
        scanf("%d", &value);
        while (getchar() != '\n') // Clear input buffer
            ;
    } while (value < min || value > max);
    return value;
}

static int getValidBet(int wallet, const char *prompt)
{
    int bet;
    do
    {
        printf(prompt);
        scanf("%d", &bet);
        while (getchar() != '\n')
            ;
    } while (bet < 0 || bet > wallet);
    return bet;
}
