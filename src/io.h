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
size_t getString(WINDOW * w, char buffer[], size_t n, const char * question);

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

#endif
