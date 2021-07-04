#ifndef DEFS_H
#define DEFS_H

/* DEBUG DEFS */
#define DEBUG /* Define when using GDB. */

/* PLAYER RELATED DEFS */
#define NAME_LEN 32
#define MAX_PLAYERS 4
#define STARTING_BAL 100

/* WINDOW AND IO RELATED DEFS */
#define NUM_OPTIONS 2
#define MAX_OPTION_SIZE 8
#define BUF_LEN 32

/* CARD RELATED DEFS */
/* Maximum size of a card name, such as "10d " (10 of Diamonds). */
#define MAX_CARD_STR 4

/* How many lines to use for printing hands. */
#define NUM_CARD_LINES 2

/* STRING LITERALS */
#define STR_NUM_PLAYERS "How many players? (Max 4) "

#endif
