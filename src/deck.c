/* Included via deck.h: <stdlib.h> */
#include <assert.h>
#include <stdio.h>
#include <time.h> /* For RNG seeding */
#include "deck.h"

const char suitChars[] = "dhsc";
const char rankChars[] = "AxxxxxxxxxJQK"; /* Ace, placeholders, Jack, Queen, King. */

Deck * initDeck(int fillCards)
{
    Deck * newDeck = malloc(sizeof(Deck));

    newDeck->size = 0;

    if (fillCards) {
        for (size_t currentSuit = 0; currentSuit < NUM_SUITS; currentSuit++) {
            for (size_t currentRank = 0; currentRank < NUM_RANKS; currentRank++) {
                Card * newCard = initCard(currentSuit, currentRank);
                pushCard(newDeck, newCard);
            } 
        }
    }

    return newDeck;
}


void deinitDeck(Deck * deck)
{
    while (deck->size > 0) {
        Card * removedCard = popCard(deck);
        deinitCard(removedCard);
    }
}


Card * popCard(Deck * deck)
{
    return removeCard(deck, 0);
}


void pushCard(Deck * deck, Card * cardToAdd)
{
    addCard(deck, cardToAdd, 0);
}


void addCard(Deck * deck, Card * cardToAdd, size_t pos)
{
    size_t currentIndex = 0;
    Card * currentCard = deck->top;
    Card * previousCard = NULL;

    assert(pos <= deck->size);

    while (currentIndex < pos) {
        previousCard = currentCard;
        currentCard = currentCard->next;
    }

    if (previousCard != NULL) {
        previousCard->next = cardToAdd;
    } else { /* Implies the first index of the deck. */
        deck->top = cardToAdd;
    }
    cardToAdd->next = currentCard;

    deck->size++;
}


Card * removeCard(Deck * deck, size_t pos)
{
    size_t currentIndex = 0;
    Card * currentCard = deck->top;
    Card * previousCard = NULL;

    while (currentCard != NULL && currentIndex < pos) {
        previousCard = currentCard;
        currentCard = currentCard->next;
        currentIndex++;
    }

    if (currentCard != NULL) {
        if (previousCard != NULL) {
            previousCard->next = currentCard->next;
        } else {
            deck->top = currentCard->next;
        }
    }

    currentCard->next = NULL;

    deck->size--;

    return currentCard;
}


Card * initCard(Suit suit, Rank rank)
{
    Card * newCard = malloc(sizeof(Card));

    newCard->suit = suit;
    newCard->rank = rank;

    return newCard;
}


void deinitCard(Card * card)
{
    free(card);
}


void printDeck(Deck * deck, int withBraces)
{
    if (withBraces) printf("<< ");

    size_t currentIndex = 0;
    Card * currentCard = deck->top;

    while (currentIndex < deck->size) {

        char currentRankChar = rankChars[currentCard->rank];
        char currentSuitChar = suitChars[currentCard->suit];

        /* 
         * Certain card types (face cards, etc) need special treatment.
         * this is determined by the placeholder value of 'x'.
         */
        if (currentRankChar != 'x') {
            printf("%c%c", currentRankChar, currentSuitChar);
        } else {
            printf("%u%c", currentCard->rank + 1, currentSuitChar);
        }

        /* Add a space only if the current card is not the last. */
        if (currentIndex < deck->size - 1) printf(" ");

        currentCard = currentCard->next;
        currentIndex++;
        
    }

    if (withBraces) printf(" >>");
}


void initShuffler()
{
    srand(time(NULL));
}


void shuffleDeck(Deck * deck)
{
    Deck * tempDeck = initDeck(0);

    /* Grab cards from the deck randomly, and store them away. */
    while (deck->size > 0) {
        pushCard(tempDeck, removeCard(deck, rand() % deck->size));
    }

    deck->top = tempDeck->top;
    deck->size = tempDeck->size;

    /* 
     * If top and size are not erased here, deinitDeck() will
     * segfault or remove all the cards associated with deck.
     */
    tempDeck->top = NULL;
    tempDeck->size = 0;
    deinitDeck(tempDeck);
}
