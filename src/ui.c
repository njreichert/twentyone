/* Included in ui.h: <curses.h> */
#include <stdlib.h>
#include "ui.h"
#include "player.h"

ScreenWrapper * initScreenWrapper()
{
    ScreenWrapper * newScreen = calloc(1, sizeof(ScreenWrapper));

    initscr();

    /* Populate rows and cols. */
    getmaxyx(stdscr, newScreen->rows, newScreen->cols);

    return newScreen;
}

void deinitScreenWrapper(ScreenWrapper * s)
{
    for (size_t i = 0; i < s->numWindows; i++)
    {
        deinitWindow(s->wins[i]);
    }

    endwin();
}

WindowWrapper * initWindowWrapper(int startY, int startx, int rows, int cols, int border)
{
    /* TODO */
}

void addWindowWrapper(WindowWrapper * w, ScreenWrapper * s)
{
    /* TODO */
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

void keypadSet(WindowWrapper * w, int isEnabled)
{
    if (isEnabled) {
        keypad(w->win, 1);
        w -> isKeypad = 1;
    } else {
        nocbreak();
        w -> isKeypad = 0;
    }
}

void initUI(ScreenWrapper * s, int isBorder, Player * players[])
{
    /* Running total for bottomWindow. */
    int totalRowsUsed = 0;

    /* Calculate the vertical size of the top section. */
    int topRows = (int) (s->rows * TOP_VERT);
    totalRowsUsed += topRows;

    /* Initialize the top section. */
    WindowWrapper * topWindow = initWindowWrapper(0, 0, topRows, s->cols, isBorder);
    addWindowWrapper(topWindow, s);

    /* 
     * The middle section is split into one window for each player, 
     * so columns need to be accounted for similarly.
     */ 
    int middleRows = (int) (s->rows * MID_VERT);

    /* NUM_PLAYERS is implied to be an int, so no rounding/casting needed. */
    int middleCols = s->cols / NUM_PLAYERS;
    int middleColsUsed = 0;

    WindowWrapper * playerTemp;

    /* Set up and attach player windows. Handle the final player seperately. */
    for (size_t i = 0; i < NUM_PLAYERS - 1; i++) {
        playerTemp = initWindowWrapper(totalRowsUsed, middleColsUsed, middleRows, middleCols, isBorder);
        middleColsUsed += middleCols;

        players[i]->win = playerTemp;
    }

    playerTemp = initWindowWrapper(totalRowsUsed, middleColsUsed, middleRows, s->cols - middleColsUsed, isBorder);
    players[NUM_PLAYERS - 1]->win = playerTemp;

    totalRowsUsed += middleRows;
    
    WindowWrapper * bottomWindow = initWindowWrapper(totalRowsUsed, 0, s->rows - totalRowsUsed, s->cols, isBorder);
    addWindowWrapper(bottomWindow, s);
}
