#include "deck.h"

#define NAME_LEN 32

typedef enum {
    HIT,
    STAND,
    BUST,
    BROKE,
    NOSTATUS
} PlayerStatus;

/**
 * @brief A player/NPC.
 */
typedef struct {
    char name[NAME_LEN + 1];
    Deck * hand;
    unsigned int balance;
    unsigned int currentBet;
    PlayerStatus status;
} Player;
