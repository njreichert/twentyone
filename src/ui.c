/* Included in ui.h: <curses.h>, "player.h" */
#include <stdlib.h>
#include <assert.h>
#include "ui.h"
#include "defs.h"
#include "io.h"

ScreenWrapper * initScreenWrapper()
{
    ScreenWrapper * newScreen = calloc(1, sizeof(ScreenWrapper));

    initscr();
    curs_set(0);
    noecho();

    /* Populate rows and cols. */
    getmaxyx(stdscr, newScreen->rows, newScreen->cols);

    return newScreen;
}

void deinitScreenWrapper(ScreenWrapper * s)
{
    delwin(s->dealerWin);
    delwin(s->inputWin);

    for (size_t i = 0; i < MAX_PLAYERS; i++)
    {
        delwin(s->playerWins[i]);
    }

    endwin();
}

void cbreakSet(ScreenWrapper * t, int isEnabled)
{
    if (isEnabled) {
        cbreak();
        t -> isCBreak = 1;
    } else {
        nocbreak();
        t -> isCBreak = 0;
    }
}

void echoSet(ScreenWrapper * t, int isEnabled)
{
    if (isEnabled) {
        echo();
        t -> isEcho = 1;
    } else {
        noecho();
        t -> isEcho = 0;
    }
}

void refreshAll(ScreenWrapper * s)
{
    /* Start with stdscr */
    // refresh();

    wrefresh(s->dealerWin);
    wrefresh(s->inputWin);

    for (size_t i = 0; i < MAX_PLAYERS; i++) {
        wrefresh(s->playerWins[i]);
    }
}

void initUI(ScreenWrapper * s)
{
    /* Running total for bottomWindow. */
    int totalRowsUsed = 0;

    /* Calculate the vertical size of the top section. */
    int topRows = (int) (s->rows * TOP_VERT);
    totalRowsUsed += topRows;

    /* Initialize the top section. */
    WINDOW * topWindow = newwin(topRows, s->cols, 0, 0);
    s->dealerWin = topWindow;

    /* 
     * The middle section is split into one window for each player, 
     * so columns need to be accounted for similarly.
     */ 
    int middleRows = (int) (s->rows * MID_VERT);

    /* MAX_PLAYERS is implied to be an int, so no rounding/casting needed. */
    int middleCols = s->cols / MAX_PLAYERS;
    int middleColsUsed = 0;

    /* Set up and attach player windows. Handle the final player seperately. */
    for (size_t i = 0; i < MAX_PLAYERS - 1; i++) {
        s->playerWins[i] = newwin(middleRows, middleCols, totalRowsUsed, middleColsUsed);
        middleColsUsed += middleCols;
    }

    s->playerWins[MAX_PLAYERS - 1] = newwin(middleRows, s->cols - middleColsUsed, totalRowsUsed, middleColsUsed);

    totalRowsUsed += middleRows;
    
    WINDOW * bottomWindow = newwin(s->rows - totalRowsUsed, s->cols, totalRowsUsed, 0);
    s->inputWin = bottomWindow;
} /* Remember to draw the screen afterwards! */

void redrawWindowBorders(WINDOW * w)
{
    werase(w);
    box(w, 0, 0);
    wrefresh(w);
}

void drawScreen(ScreenWrapper * s, Player * players[], Player * dealer)
{
    /* Draw Dealer Window, Input Window, then Player Windows. */
    redrawWindowBorders(s->dealerWin);
    printPlayerInfo(s->dealerWin, dealer);

    redrawWindowBorders(s->inputWin);

    for (size_t i = 0; i < MAX_PLAYERS; i++) {
        redrawWindowBorders(s->playerWins[i]);
        if (players[i]->status != NOT_PLAYING) {
            if (players[i]->status == CUR_PLAYER) {
                attron(A_BOLD);
            }
            printPlayerInfo(s->playerWins[i], players[i]);
            attroff(A_BOLD); /* TODO: Does this need to be in an if statement like above? */
        }
    }

    refreshAll(s);
}

