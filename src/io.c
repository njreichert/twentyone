/* Included in io.h: <stdlib.h> */
#include <stdio.h>

int getLine(char buffer[], size_t n)
{
    char c;
    size_t i = 0;

    while ((c = (char) getchar()) != '\n' && c != EOF) {
        if (i < n) buffer[i++] = c;
    }

    buffer[i] = '\0';

    return i;
}