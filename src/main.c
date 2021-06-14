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

    for (size_t i = 0; i < MAX_PLAYERS; i++) {
        players[i] = initPlayer(100);
    }

    char buf[256] = "";

    ScreenWrapper * sc = initScreenWrapper();
    initUI(sc);

    noecho();

    drawScreen(sc, players, dealer);

    mvwprintw(sc->dealerWin, 1, 1, "Dealer Window: %d\t%d", getmaxy(sc->dealerWin), getmaxx(sc->dealerWin));
    refreshAll(sc);
    
    for (size_t i = 0; i < MAX_PLAYERS; i++)
    {
        mvwprintw(sc->dealerWin, i + 2, 1, "Player %d: %d\t%d", i + 1, getmaxy(sc->playerWins[i]), getmaxx(sc->playerWins[i]));
        refreshAll(sc);
    }

    const char * opt[2] = {"Option A", "Opt B"};

    mvwprintw(sc->inputWin, MAX_PLAYERS + 2, 1, "Input Window: %d\t%d", getmaxy(sc->inputWin), getmaxx(sc->inputWin));
    refreshAll(sc);
    // char c = getInput(sc->inputWin, "test test test test test test test test test", opt, "ab");

    size_t a = getString(sc, buf, 15, "What is your name? ");

    printCentred(sc->playerWins[2], 3, "test 123");

    deinitScreenWrapper(sc);

    
    printf("%lu, %s\n", a, buf);

    getchar();

    

    return EXIT_SUCCESS;
}
