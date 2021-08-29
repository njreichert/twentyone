#include "player.h"
#include "ui.h"
#include "io.h"

typedef enum WinState {
    WIN,
    PUSH,
    LOSS
} WinState;

/**
 * @brief Displays a dialog and updates the given player with their bets.
 * 
 * @param p The player in question.
 * @param s The ScreenWrapper on which to display the dialog.
 */
void betDialog(Player * p, ScreenWrapper * s);

/**
 * @brief Displays a dialog and "anykeys".
 * 
 * @param str The string to print.
 * @param s The ScreenWrapper on which to display the dialog.
 */
void textDialog(char * str, ScreenWrapper * s);

/**
 * @brief Displays a dialog and deals cards to players.
 * 
 * @param p The Player in question.
 * @param src The deck to deal cards to.
 * @param s The ScreenWrapper on which to display the dialog.
 */
void dealDialog(Player * p, Deck * src, ScreenWrapper * s);

/**
 * @brief Determines whether a player has won against the dealer.
 * 
 * @param p The Player in question.
 * @param dealer The dealer to compare against.
 * 
 * @returns the WinState of the round.
 */
WinState getRoundOutcome(Player * p, Player * dealer);