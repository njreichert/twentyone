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
} WindowWrapper;

/* 
 * The terminal as a whole. Contains a list of MAX_ELEMENTS elements and metadata
 * relating to the terminal.
 */
typedef struct Terminal {
    int rows;
    int cols;
    int isCBreak;
    int isNoEcho;
    int isKeypad;
    WindowWrapper * wins[MAX_WINDOWS];
} Terminal;

#endif
