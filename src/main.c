#include <stdlib.h>
#include <stdio.h>

#include "deck.h"
#include "ui.h"
#include "player.h"

int main(void)
{

    getchar();

    Player * players[6] = {0};

    for (size_t i = 0; i < MAX_PLAYERS; i++) {
        players[i] = initPlayer(100);
    }

    ScreenWrapper * sc = initScreenWrapper();
    initUI(sc);

    for (int i = 0; i < sc->numWindows; i++) {
        wborder(sc->wins[i], 0, 0, 0, 0, 0, 0, 0, 0);
    }

    refreshAll(sc);
    for (size_t i = 0; i < sc->numWindows; i++)
    {
        mvwprintw(sc->wins[0], i + 1, 1, "window %d: %d\t%d", i, getmaxy(sc->wins[i]), getmaxx(sc->wins[i]));
        refreshAll(sc);
    }

    deinitScreenWrapper(sc);


    getchar();

    

    return EXIT_SUCCESS;
}
