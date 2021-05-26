#ifndef UI_H
#define UI_H

#include <curses.h>
#include "player.h"

#define MAX_WINDOWS 8
#define TOP_VERT 1.0/3.0
#define MID_VERT 1.0/3.0

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
 * @brief Initalizes a curses instance and associated structs.
 * 
 * @returns the ScreenWrapper initialized.
 */
ScreenWrapper * initScreenWrapper();

/**
 * @brief Frees memory associated with a given ScreenWrapper and exits curses.
 * 
 * @param s The ScreenWrapper in question.
 */
void deinitScreenWrapper(ScreenWrapper * s);

/**
 * @brief Initializes a new window and populates metadata.
 * 
 * @param startY Starting Y position.
 * @param startX Starting X position.
 * @param rows Number of rows.
 * @param cols Number of Columns
 * @returns the new WindowWrapper struct.
 */
WindowWrapper * initWindowWrapper(int startY, int startX, int rows, int cols);

/**
 * @brief Adds a window to the given screenWrapper.
 * 
 * NOTE: Checks by assertion that s->wins is in bounds!
 * 
 * @param w The WindowWrapper to add. 
 * @param s The ScreenWrapper in question.
 */
void addWindowWrapper(WindowWrapper * w, ScreenWrapper * s);

/**
 * @brief Frees memory associated with a given window.
 * 
 * @param w The WindowWrapper to free.
 */
void deinitWindowWrapper(WindowWrapper * w);

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

/**a
 * @brief Changes the state of keypad, and stores that in the Window's metadata.
 * 
 * @param t The ScreenWrapper in question.
 * @param isEnabled Set/clear the respective property.
 */
void keypadSet(WindowWrapper * w, int isEnabled);

/**
 * @brief Refreshes all windows on screen.
 * 
 * @param s The ScreenWrapper referencing the windows.
 */
void refreshAll(ScreenWrapper * s);

/**
 * @brief Initializes various UI elements.
 * 
 * There are three sections:
 * 
 * - The top section, displaying dealer hands and other information,
 * - The middle section, displaying each players' name, hand, and balance, and
 * - The bottom section, which handles input.
 * 
 * Vertical space is determined by the double values TOP_VERT and MID_VERT 
 * for top and middle, respectively. The bottom section fills all remaining space. 
 * 
 * @param s The ScreenWrapper to store created windows in.
 * @param isBorder Draws borders on each element, if set.
 * @param players An array of player structs (to attach player windows to).
 */
void initUI(ScreenWrapper * s, int isBorder);

#endif
