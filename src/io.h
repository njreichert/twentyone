#ifndef IO_H
#define IO_H

#include <stdlib.h>

/**
 * @brief Get a line from stdin _somewhat_ safely.
 * 
 * @param buffer a char array to place the line in.
 * @param n The max number of chars to place in the buffer (usually the size of the buffer minus-one) 
 * @returns The number of chars (excluding '\0') placed into buffer.
 */
int getLine(char buffer[], size_t n);

#endif
