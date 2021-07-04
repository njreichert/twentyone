#include <stdlib.h>
#include <stdio.h>

#include "deck.h"
#include "ui.h"
#include "player.h"
#include "io.h"
#include "game.h"
#include "defs.h"

int main(void)
{

    #ifdef DEBUG
        printf("Waiting for GDB... Press Enter when ready.")
        getchar();
    #endif

    /*
     * Initialize all datastructures. 
     * Players will be setup when we have a UI to do so.
     */
    Player * players[MAX_PLAYERS] = {0};
    Player * dealer = initPlayer(STARTING_BAL, "Dealer");

    ScreenWrapper * sc = initScreenWrapper();

    Deck * d = initDeck(1);
    shuffleDeck(d);

    /* Setup UI, players, then game for first deal */
    initUI(sc);

    /* Setup players. */

    return EXIT_SUCCESS;
}
