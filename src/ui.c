/* Included in ui.h: <curses.h> */
#include <stdlib.h>
#include <assert.h>
#include "ui.h"
#include "defs.h"

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
        delwin(s->wins[i]);
        s->numWindows -= 1;
    }

    endwin();
}

/* Windows should not be removed as easily as they are added (static elements), so no remove fn here. */
void addWindow(WINDOW * w, ScreenWrapper * s)
{
    assert(s->numWindows + 1 <= MAX_WINDOWS);

    s->wins[s->numWindows] = w;
    s->numWindows += 1;
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
    refresh();

    for (size_t i = 0; i < s->numWindows; i++) {
        wrefresh(s->wins[i]);
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
    addWindow(topWindow, s);

    /* 
     * The middle section is split into one window for each player, 
     * so columns need to be accounted for similarly.
     */ 
    int middleRows = (int) (s->rows * MID_VERT);

    /* MAX_PLAYERS is implied to be an int, so no rounding/casting needed. */
    int middleCols = s->cols / MAX_PLAYERS;
    int middleColsUsed = 0;

    WINDOW * middleWin;

    /* Set up and attach player windows. Handle the final player seperately. */
    for (size_t i = 0; i < MAX_PLAYERS - 1; i++) {
        middleWin = newwin(middleRows, middleCols, totalRowsUsed, middleColsUsed);
        middleColsUsed += middleCols;

        addWindow(middleWin, s);
    }

    middleWin = newwin(middleRows, s->cols - middleColsUsed, totalRowsUsed, middleColsUsed);
    addWindow(middleWin, s);

    totalRowsUsed += middleRows;
    
    WINDOW * bottomWindow = newwin(s->rows - totalRowsUsed, s->cols, totalRowsUsed, 0);
    addWindow(bottomWindow, s);
}

void drawBorders(ScreenWrapper * s)
{
    for (int i = 0; i < s->numWindows; i++) {
        box(s->wins[i], 0, 0);
    }
}
