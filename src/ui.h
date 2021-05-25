#ifndef UI_H
#define UI_H

#include <curses.h>

#define MAX_WINDOWS 8

typedef enum ElementType {
    GENERIC,
    INPUTBOX,
    STATUSBOX,
} ElementType;

/* A window in curses, with extra metadata to aid in redrawing if need be. */
typedef struct WindowWrapper {
    WINDOW * win;
    int y; /** Initial vertical location. Zero-indexed. */
    int x; /** Initial horizontal location. Zero-indexed. */
    int rows;
    int cols;
    int priority; /** Determines order at which Elements will be rendered. */
    int isKeypad;
} WindowWrapper;

/* 
 * The terminal as a whole. Contains a list of MAX_ELEMENTS elements and metadata
 * relating to the terminal.
 */
typedef struct Terminal {
    int rows;
    int cols;
    /** Various properties for the screen and its windows. */
    int isCBreak;
    int isNoecho;
    WindowWrapper * wins[MAX_WINDOWS];
} Terminal;

/**
 * @brief Changes the state of cbreak, and stores that in the terminal.
 * 
 * @param t The terminal in question.
 * @param isEnabled Set/clear the respective property.
 */
void cbreakSet(Terminal * t, int isEnabled);

/**
 * @brief Changes the state of noecho, and stores that in the terminal.
 * 
 * @param t The terminal in question.
 * @param isEnabled Set/clear the respective property.
 */
void noechoSet(Terminal * t, int isEnabled);

/**
 * @brief Changes the state of keypad, and stores that in the terminal.
 * 
 * @param t The terminal in question.
 * @param isEnabled Set/clear the respective property.
 */
void keypadSet(WindowWrapper * w, int isEnabled);

#endif
