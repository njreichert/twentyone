#ifndef UI_H
#define UI_H

#include <curses.h>

typedef enum ElementType {
    GENERIC,
    INPUTBOX,
    STATUSBOX,
} ElementType;

/* A window in curses, with extra metadata. */
typedef struct Element {
    WINDOW * win;
    int y; /** Vertical Location. Zero-indexed. */
    int x; /** Horizontal location. Zero-indexed. */
    int rows;
    int cols;
    int priority; /** Determines order at which Elements will be rendered. */
} Element;

#endif
