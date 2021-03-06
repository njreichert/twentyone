#ifndef DEFS_H
#define DEFS_H

/* PLAYER RELATED DEFS */
#define NAME_LEN 16
#define MAX_PLAYERS 4
#define STARTING_BAL 100

/* GAMEPLAY RELATED DEFS */
#define SOFT_STOP 17

/* WINDOW AND IO RELATED DEFS */
#define NUM_OPTIONS 2
#define MAX_OPTION_SIZE 8
#define BUF_LEN 64
#define WINDOW_PADDING 1
#define MAX_STR_INPUT 16
#define ANYKEY "Press any key to continue..."

/* CARD RELATED DEFS */
#define MAX_CARD_STR 4

/* GAME RELATED DEFS */
#define PAYOUT 1.5 /* 3 to 2 */

/* STRING LITERALS */
#define STR_NUM_PLAYERS "How many players? (Max 4) "

/* COLOUR DEFS */
#define MAIN_PAIR 1
/* Colours RGB Channels are from [0, 1000]. */
#define GREEN_R 0
#define GREEN_G 484
#define GREEN_B 281
#define WHITE_RGB 1000

#endif
