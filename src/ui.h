#ifndef UI_H
#define UI_H

#include <curses.h>

typedef enum ElementType {
    GENERIC,
    INPUTBOX,
    STATUSBOX,
} ElementType;

/* A window in curses, with extra metadata to aid in redrawing if need be. */
typedef struct Element {
    WINDOW * win;
    int y; /** Initial vertical location. Zero-indexed. */
    int x; /** Initial horizontal location. Zero-indexed. */
    int rows;
    int cols;
    int priority; /** Determines order at which Elements will be rendered. */
} Element;

#endif
