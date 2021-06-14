#ifndef IO_H
#define IO_H

#include <stdlib.h>

#define IS_BACKSPACE(c) (c == KEY_BACKSPACE || c == 127 || c == '\b')


/**
 * @brief Gets a String and places it into buffer
 * 
 * NB: Assumes buffer has a size of n+1!
 * 
 * @param w The window to display on.
 * @param buffer The buffer to place chars in.
 * @param n The max number of chars to get from the user.
 * @param question A string denoting a question to ask the user.
 * @returns the number of chars entered into buffer. 
 */
size_t getString(ScreenWrapper * s, char buffer[], size_t n, const char * question);

/**
 * @brief Prompts the user with options and gets a single key.
 * 
 * NOTE: Checks by assertion that there are as many chars in keys
 * as there are strings in options. (One key per option.)
 * 
 * @param w The window to display on.
 * @param question A string denoting a question to ask the user.
 * @param options An array of strings denoting options.
 * @param keys A string denoting each key to be pressed. 
 * @returns the key code of the char pressed.
 */
char getInput(WINDOW * w, const char * question, const char * options[], const char * keys);

/**
 * @brief Prints a string centred to the given window.
 * 
 * @param w The window to print to.
 * @param y The vertical position of the string.
 * @param str The string to print.
 * 
 * @returns 1 on success, 0 on failure (likely if the string is larger than the window size).
 */
int printCentred(WINDOW * w, int y, const char * str);

/**
 * @brief Attempts to print the given deck to the window, in up to two lines.
 * 
 * @param w The window to print to.
 * @param y The beginning vertical position.
 * @param d The Deck to print.
 * 
 * @returns 1 on success, 0 on failure.
 */
int printHand(WINDOW * w, int y, Deck * d);

#endif
