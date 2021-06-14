/* Included in io.h: <stdlib.h> */
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <assert.h>
#include "ui.h"
#include "io.h"
#include "defs.h"
#include "deck.h"

/* TODO: Fix any possible off-by-one errors with padding / cursor movement. */

size_t getString(ScreenWrapper * s, char buffer[], size_t n, const char * question)
{

    WINDOW * ioWin = s->inputWin;
    int c; /* wgetch has a couple of useful non-char (8-bit) characters for arrow keys or backspace, etc. */
    size_t i = 0;

    redrawWindowBorders(ioWin);

    int centreRow = getmaxy(ioWin) / 2;
    int padding = (getmaxx(ioWin) - strlen(question) - n) / 2; /* TODO: Revisit. */

    mvwprintw(ioWin, centreRow, padding, "%s", question, n, "");

    int x = getcurx(ioWin); /* We are going to manipulate the cursor ourselves. */

    wattron(ioWin, A_UNDERLINE);
    wprintw(ioWin, "%*s", n, "");
    wrefresh(ioWin);

    cbreak();
    keypad(stdscr, TRUE);
    
    while ((c = wgetch(ioWin)) != '\n' && c != EOF) {
        
        if (IS_BACKSPACE(c)) {
            if (i > 0) {
                buffer[--i] = '\0'; /* Remove the latest char. */
                mvwaddch(ioWin, getcury(ioWin), x + i, ' ');
            }
        /* All curses keypad chars have bit 8 set (2^8). Filter out all non-backspace chars. */
        } else if (i < n && !(c & KEY_CODE_YES)) {
            buffer[i++] = (char) c;
            mvwprintw(ioWin, getcury(ioWin), x, "%.*s", n, buffer);
        }

        wrefresh(ioWin);
    }

    wattroff(ioWin, A_UNDERLINE);
    buffer[i] = '\0';

    redrawWindowBorders(ioWin);

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

    redrawWindowBorders(w);

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

int printCentred(WINDOW * w, int y, const char * str)
{
    int padding = getmaxx(w) - strnlen(str, getmaxx(w));

    if (strlen(str) > getmaxx(w)) {
        return 0;
    }

    if (y >= getmaxy(w)) {
        return 0;
    }

    mvwprintw(w, y, padding / 2, "%s", str);

    wrefresh(w);

    return 1;
}

void printPlayerInfo(WINDOW * w, Player * p)
{
    printCentred(w, 1, p->name);
    /* Print Balance and bet on the same line. */
    char buf[BUF_LEN + 1] = "";

    if (p->currentBet != 0) {
        snprintf(buf, BUF_LEN, "$%u (Betting: $%u)", p->balance, p->currentBet);
    } else {
        snprintf(buf, BUF_LEN, "$%u", 15);
    }

    printCentred(w, 2, buf);

    printHand(w, getmaxy(w) - 3, p->hand);

}

int printHand(WINDOW * w, int y, Deck * d)
{
    size_t i = 0;
    Card * currentCard = d->top;

    /* The lines are stored here before printing. */
    char buf[2][BUF_LEN + 1] = {"", ""};
    size_t buflen[2] = {0};

    size_t currentBuf = 0;

    char currentCardStr[MAX_CARD_STR + 1] = "";

    while (i < d->size) {

        char currentRankChar = getRankChar(currentCard);
        char currentSuitChar = getSuitChar(currentCard);

        /* Check if the given line will overflow after another card (worst case) */
        if (buflen[currentBuf] + MAX_CARD_STR > getmaxx(w) - 2) {
            if (currentBuf == 0) {
                currentBuf = 1;
            } else {
                return 0; /* Failure */
            }
        }
        /* TODO: ADD SPACING, and other things to this. THIS NEEDS TO BE FINISHED FIRST. */

        /* 
         * Certain card types (face cards, etc) need special treatment.
         * this is determined by the placeholder value of 'x'.
         */
        if (currentRankChar != 'x') {
            snprintf(currentCardStr, "%c%c", BUF_LEN, currentRankChar, currentSuitChar);
        } else {
            snprintf(currentCardStr, "%u%c", BUF_LEN, currentCard->rank + 1, currentSuitChar);
        }

        strncat(buf[currentBuf], currentCardStr, MAX_CARD_STR);
        buflen[currentBuf] += strnlen(currentCardStr, MAX_CARD_STR);

        /* Add a space only if the current card is not the last. */
        if (i < d->size - 1) printf(" ");

        currentCard = currentCard->next;
        i++;
        
    }
}
