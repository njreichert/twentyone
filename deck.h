#ifndef DECK_H
#define DECK_H

#include <stdlib.h>

typedef enum SUIT {
    DIAMONDS,
    HEARTS,
    SPADES,
    CLUBS
} SUIT;

typedef char Rank;

/**
 * @brief A Deck. Effectively a linked list of Cards with extra metadata. 
 */
typedef struct deck {
    Card top; /**< The linked list of cards. */
    size_t size; /**< Must be changed manually. */
};

/**
 * @brief A Card. A linked list node with data for suit and rank. 
 */
typedef struct Card {
    SUIT suit;
    Rank rank;
    Card *next; /**< The pointer to the next card. */
};

#endif