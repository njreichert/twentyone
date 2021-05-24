#include <stdlib.h>
#include <stdio.h>

#include "deck.h"

int main(void)
{
    Deck * deckOne = initDeck(1);

    printf("Preshuffle: ");
    printDeck(deckOne, 0);
    printf("\n");

    shuffleDeck(deckOne);
    printf("PostShuffle: ");
    printDeck(deckOne, 1);
    printf("\n");

    

    return EXIT_SUCCESS;
}
