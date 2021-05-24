/* Included in player.h: "deck.h" */
#include <stdlib.h>
#include "player.h"

Player * initPlayer(unsigned int startingBalance)
{
    /* TODO: Sanity-check the zero-ness of this. */
    Player * newPlayer = calloc(1, sizeof(Player));

    newPlayer->status = NO_STATUS;
    newPlayer->hand = initDeck(0);
}

void deinitPlayer(Player * player)
{
    deinitDeck(player->hand);
    free(player);
}