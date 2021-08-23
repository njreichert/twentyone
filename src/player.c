/* Included in player.h: "deck.h", "ui.h", "defs.h" */
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

Player * initPlayer(unsigned int startingBalance, char * name)
{
    /* TODO: Sanity-check the zero-ness of this. */
    Player * newPlayer = calloc(1, sizeof(Player));

    newPlayer->status = NOT_PLAYING;
    newPlayer->balance = startingBalance;
    newPlayer->hand = initDeck(0);
    snprintf(newPlayer->name, NAME_LEN, "%s", name);

    return newPlayer;
}

void deinitPlayer(Player * player)
{
    deinitDeck(player->hand);
    free(player);
}
