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
 * The screen as a whole. Contains a list of MAX_ELEMENTS WindowWrappers and metadata
 * relating to the list of windows.
 */
typedef struct ScreenWrapper {
    int rows;
    int cols;
    /** Various properties for the screen and its windows. */
    int isCBreak;
    int isEcho;
    WindowWrapper * wins[MAX_WINDOWS];
    size_t numWindows;
} ScreenWrapper;

/**
 * @brief Changes the state of cbreak, and stores that in the ScreenWrapper.
 * 
 * @param s The ScreenWrapper in question.
 * @param isEnabled Set/clear the respective property.
 */
void cbreakSet(ScreenWrapper * s, int isEnabled);

/**
 * @brief Changes the state of noecho, and stores that in the ScreenWrapper.
 * 
 * @param s The ScreenWrapper in question.
 * @param isEnabled Set/clear the respective property.
 */
void noechoSet(ScreenWrapper * s, int isEnabled);

/**
 * @brief Changes the state of keypad, and stores that in the Window's metadata.
 * 
 * @param t The ScreenWrapper in question.
 * @param isEnabled Set/clear the respective property.
 */
void keypadSet(WindowWrapper * w, int isEnabled);

#endif
