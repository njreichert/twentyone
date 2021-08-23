#include <stdlib.h>
#include <stdio.h>

#include "deck.h"
#include "ui.h"
#include "player.h"
#include "io.h"

int main(void)
{

    getchar();

    Player * players[6] = {0};
    Player * dealer = {0};
    Deck * deck = initDeck(1);

    int i = 0;

    char pname[NAME_LEN + 1];

    for (size_t i = 0; i < MAX_PLAYERS; i++) {
        snprintf(pname, NAME_LEN, "player%lu", i);
        players[i] = initPlayer(100, pname);
        players[i]->status = NO_STATUS;
    }

    players[2]->status = CUR_PLAYER;

    snprintf(pname, NAME_LEN, "player%d", i);
    dealer = initPlayer(1000, pname);

    ScreenWrapper * sc = initScreenWrapper();
    initUI(sc);

    noecho();

    drawScreen(sc, players, dealer);

    for (size_t i = 0; i < 20; i++)
    {
        dealCard(deck, players[0]->hand, 1);
        drawScreen(sc, players, dealer);
    }
    

    deinitScreenWrapper(sc);

    getchar();

    

    return EXIT_SUCCESS;
}
