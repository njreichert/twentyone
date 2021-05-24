#ifndef DECK_H
#define DECK_H

#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4

/* 
 * Suit definitions. Easier to iterate through so long as the values
 * Are well-defined. 
 */
#define DIAMONDS 0
#define HEARTS 1
#define SPADES 2
#define CLUBS 3

typedef unsigned char Suit;
typedef unsigned char Rank;

/**
 * @brief A Card. A linked list node with data for suit and rank. 
 */
typedef struct Card {
    Suit suit;
    Rank rank;
    struct Card * next; /** The pointer to the next card. */
} Card;

/**
 * @brief A Deck. Effectively a linked list of Cards with extra metadata. 
 */
typedef struct Deck {
    Card * top; /** The linked list of cards. */
    size_t size; /** Must be changed manually. */
} Deck;

/* Function Definitions */


/**
 * @brief Initializes a new deck.
 * 
 * @param fillCards will fill the deck with (NUM_RANKS * NUM_SUITS) Cards.
 * @returns a pointer to the new deck.
 */
Deck * initDeck(int fillCards);

/**
 * @brief Cleans up and frees memory associated with a deck.
 * 
 * @param deck The deck in question.
 */
void deinitDeck(Deck * deck);

/**
 * @brief An alias for removeCard() at position 0.
 * 
 * @param deck The deck in question.
 * @return The card removed.
 */
Card * popCard(Deck * deck);

/**
 * @brief A wrapper for addCard(deck, 0).
 * 
 * @param deck The deck in question.
 * @param cardToAdd The card to add.
 */
void pushCard(Deck * deck, Card * cardToAdd);

/**
 * @brief Adds a card at a given position.
 * 
 * NOTE: This function checks by assertion that the position is within the bounds of the deck. 
 * 
 * @param deck The deck in question.
 * @param cardToAdd The card in question.
 * @param pos The position to add a card to.
 */
void addCard(Deck * deck, Card * cardToAdd, size_t pos);

/**
 * @brief Removes the card at a given position.
 * 
 * @param deck The deck in question.
 * @param pos The position to remove.
 * @return A pointer to the card removed with its next member set to NULL. Returns NULL if the index is out of bounds.
 */
Card * removeCard(Deck * deck, size_t pos);

/**
 * @brief Creates a card with a rank and suit.
 * 
 * Users of this function must modify Card.next to their liking.
 * 
 * @param suit 
 * @param rank 
 * @return a pointer to the new card.
 */
Card * initCard(Suit suit, Rank rank);

/**
 * @brief A wrapper to free(card). Frees the memory associated with the card.
 * 
 * @param card The card in question.
 */
void deinitCard(Card * card);

/**
 * @brief Prints a representation of the deck.
 * 
 * @param deck The deck in question.
 * @param withBraces will add braces to the beginning and end of the string.
 */
void printDeck(Deck * deck, int withBraces);

/**
 * @brief Initializes the RNG. Effectively a wrapper for srand(time(NULL)).
 * 
 */
void initShuffler();

/**
 * @brief Shuffles the deck in place by randomly selecting cards and placing them into a temporary deck.
 * 
 * @param deck The deck to shuffle.
 */
void shuffleDeck(Deck * deck);

#endif