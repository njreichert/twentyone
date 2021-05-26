#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"
#include "ui.h"
#include "defs.h"

#define NAME_LEN 32

typedef enum PlayerStatus {
    HIT,
    STAND,
    BUST,
    BROKE,
    NO_STATUS
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
    WindowWrapper * win; /** Place player info here. */
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
 * @returns a pointer to the player. 
 */
Player * initPlayer(unsigned int startingBalance);


/**
 * @brief Frees memory associated with the current player. 
 * 
 * NOTE: Will remove all cards associated with the player's hand.
 * 
 * @param player The player to remove.
 */
void deinitPlayer(Player * player);

#endif
