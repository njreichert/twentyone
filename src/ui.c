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
        deinitWindowWrapper(s->wins[i]);
        s->numWindows -= 1;
    }

    endwin();
}

WindowWrapper * initWindowWrapper(int startY, int startX, int rows, int cols)
{
    WindowWrapper * newWindow = malloc(sizeof(WindowWrapper));

    newWindow->win = newwin(rows, cols, startY, startX);
    newWindow->y = startY;
    newWindow->x = startX;
    newWindow->rows = rows;
    newWindow->cols = cols;

    return newWindow;
}

/* Windows should not be removed as easily as they are added (static elements), so no remove fn here. */
void addWindowWrapper(WindowWrapper * w, ScreenWrapper * s)
{
    assert(s->numWindows + 1 <= MAX_WINDOWS);

    s->wins[s->numWindows] = w;
    s->numWindows += 1;
}

void deinitWindowWrapper(WindowWrapper * w)
{
    delwin(w->win);
    free(w);
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

void refreshAll(ScreenWrapper * s)
{
    /* Start with stdscr */
    refresh();

    for (size_t i; i < s->numWindows; i++) {
        wrefresh(s->wins[i]->win);
    }
}

void initUI(ScreenWrapper * s, int isBorder)
{
    /* Running total for bottomWindow. */
    int totalRowsUsed = 0;

    /* Calculate the vertical size of the top section. */
    int topRows = (int) (s->rows * TOP_VERT);
    totalRowsUsed += topRows;

    /* Initialize the top section. */
    WindowWrapper * topWindow = initWindowWrapper(0, 0, topRows, s->cols);
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
        playerTemp = initWindowWrapper(totalRowsUsed, middleColsUsed, middleRows, middleCols);
        middleColsUsed += middleCols;

        addWindowWrapper(playerTemp, s);
    }

    playerTemp = initWindowWrapper(totalRowsUsed, middleColsUsed, middleRows, s->cols - middleColsUsed);

    totalRowsUsed += middleRows;
    
    WindowWrapper * bottomWindow = initWindowWrapper(totalRowsUsed, 0, s->rows - totalRowsUsed, s->cols);
    addWindowWrapper(bottomWindow, s);
}
