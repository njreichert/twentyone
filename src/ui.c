/* Included in ui.h: <curses.h> */
#include "ui.h"

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
