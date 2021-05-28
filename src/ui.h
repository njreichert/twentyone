#ifndef UI_H
#define UI_H

#include <curses.h>

#define MAX_WINDOWS 8
#define TOP_VERT 1.0/3.0
#define MID_VERT 1.0/3.0

typedef enum ElementType {
    GENERIC,
    INPUTBOX,
    STATUSBOX,
} ElementType;

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
    WINDOW * dealerWin;
    WINDOW * playerWins[MAX_WINDOWS];
    WINDOW * inputWin;
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
 */
void initUI(ScreenWrapper * s);

/**
 * @brief Draws inside borders on all windows.
 * 
 * @param s The ScreenWrapper containing the windows to place borders on.
 */
void drawBorders(ScreenWrapper * s);

#endif
