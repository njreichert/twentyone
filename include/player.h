#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"
#include "defs.h"

typedef enum PlayerStatus {
    CUR_PLAYER,
    PLAYING,
    STAND,
    BUST,
    BROKE,
    BLACKJACK, /* 21 via initial deal. */
    TWENTY_ONE, /* 21 via hitting. */
    NOT_PLAYING, /* Probably haven't played yet. */
} PlayerStatus;

/**
 * @brief A player/NPC.
 */
typedef struct Player {
    char name[NAME_LEN + 1];
    Deck * hand;
    unsigned int balance;
    unsigned int currentBet;
    PlayerStatus status;
} Player;


/**
 * @brief Initializes a player with some money to start.
 * 
 * Initial member values:
 * name: A null array.
 * hand: A new Deck pointer.
 * balance: startingBalance.
 * currentBet: 0.
 * status: NO_STATUS.
 * 
 * @param startingBalance The amount of mney the player should start with. 
 * @param name The new player's name.
 * @returns a pointer to the player. 
 */
Player * initPlayer(unsigned int startingBalance, char * name);


/**
 * @brief Frees memory associated with the current player. 
 * 
 * NOTE: Will remove all cards associated with the player's hand.
 * 
 * @param player The player to remove.
 */
void deinitPlayer(Player * player);

/**
 * @brief Checks if all players have zero dollars.
 * 
 * @param p The list of players to check.
 * @param n The numebr of players to check
 * 
 * @returns a non-zero value if all players are broke.
 * 
 */
int allPlayersBroke(Player * p[], size_t n);

/**
 * @brief Checks if any players are not broke, bust, or standing.
 * 
 * @param p An array of Players.
 * @param n The number of players to check.
 * @returns a non-zero value if any players have status == PLAYING.
 */
int anyPlayersPlaying(Player * p[], size_t n);

#endif
