/* Included in io.h: <stdlib.h> */
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <assert.h>
#include "io.h"
#include "defs.h"

/* TODO: Fix any possible off-by-one errors with padding / cursor movement. */

size_t getString(WINDOW * w, char buffer[], size_t n, const char * question)
{
    int c; /* wgetch has a couple of useful non-char (8-bit) characters for arrow keys or backspace, etc. */
    size_t i = 0;

    int centreRow = getmaxy(w) / 2;
    int padding = (getmaxx(w) - strlen(question) - n) / 2; /* TODO: Revisit. */

    mvwprintw(w, centreRow, padding, "%s", question, n, "");

    int x = getcurx(w); /* We are going to manipulate the cursor ourselves. */

    wattron(w, A_UNDERLINE);
    wprintw(w, "%*s", n, "");
    wrefresh(w);

    

    cbreak();
    keypad(stdscr, TRUE);
    
    while ((c = getch()) != '\n' && c != EOF) {
        
        if (IS_BACKSPACE(c)) {
            if (i > 0) {
                buffer[--i] = '\0'; /* Remove the latest char. */
                mvwaddch(w, getcury(w), x + i, ' ');
            }
        /* All curses keypad chars have bit 8 set (2^8). Filter out all non-backspace chars. */
        } else if (i < n && !(c & KEY_CODE_YES)) {
            buffer[i++] = (char) c;
            mvwprintw(w, getcury(w), x, "%.*s", n, buffer);
        }

        wrefresh(w);
    }

    wattroff(w, A_UNDERLINE);
    buffer[i] = '\0';

    return i;
}

char getInput(WINDOW * w, const char * question, const char * options[], const char * keys)
{
    /* TODO: revisit */
    assert(strlen(keys) == NUM_OPTIONS);

    for (size_t i = 0; i < NUM_OPTIONS; i++)
    {
        assert(strlen(options[i]) <= MAX_OPTION_SIZE);
    }

    int padding;

    werase(w);
    wrefresh(w); /* REMOVE */

    box(w, 0, 0);
    wrefresh(w);

    /* 
     * Calculate positions of text elements semi-arbitrarily. 
     * Assumes borders are shown (hence the '-1').
     */
    int centreRow = getmaxy(w) / 2;
    padding = ((getmaxx(w) - strlen(question)) / 2) - 1; /* TODO: Revisit. */

    mvwprintw(w, centreRow - 2, 1, "%*s%s", padding, "", question);
    wrefresh(w); /* REMOVE */
    
    char optionBuffer[BUF_LEN] = "";

    for (size_t i = 0; i < NUM_OPTIONS; i++)
    {
        char tempOption[BUF_LEN] = "";
        sprintf(tempOption, "%c) %s", keys[i], options[i]);

        strcat(optionBuffer, tempOption);

        if (i != NUM_OPTIONS - 1) { /* Not the last option. */
            strcat(optionBuffer, "        ");
        }
    }
    
    padding = ((getmaxx(w) - strlen(optionBuffer)) / 2) - 1;

    mvwprintw(w, centreRow + 1, 1, "%*s%s", padding, "", optionBuffer);
    wrefresh(w);

    /** Set up stdscr for one char, no echo input. */
    cbreak();
    char c = getch();
    nocbreak();
    

    return c;

    /* TODO: Check if stdin needs to be flushed, like in getline(). */
}