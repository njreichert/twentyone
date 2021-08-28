#include <stdlib.h>
#include <stdio.h>

#include "deck.h"
#include "ui.h"
#include "player.h"
#include "io.h"
#include "game.h"

int main(void)
{

    printf("Press any key to continue...\n");
    getchar();

    Player * players[MAX_PLAYERS] = {0};
    Player * dealer = {0};
    Deck * deck = initDeck(1);

    char printBuf[BUF_LEN + 1];

    dealer = initPlayer(1000, "Dealer");

    ScreenWrapper * sc = initScreenWrapper();
    initUI(sc);
    noecho();
    refreshAll(sc);

    size_t numPlayers = (size_t) (getNum(sc, MAX_PLAYERS, "How many players? "));

    for (size_t i = 0; i < numPlayers; i++) {

        char pName[NAME_LEN + 1] = "";

        snprintf(printBuf, BUF_LEN, "Player %lu's name? ", i + 1);
        getString(sc, pName, NAME_LEN, printBuf);

        players[i] = initPlayer(100, pName);
        players[i]->status = PLAYING;
    }

    drawScreen(sc, players, numPlayers, dealer);

    /* Main game loop */
    while (!allPlayersBroke(players, numPlayers)) {

        for (size_t i = 0; i < numPlayers; i++) {
            if (players[i]->status != BROKE) {
                betDialog(players[i], sc); /* TODO */
            }
        }

        /* First two deals. */
        /* TODO: Maybe make the dealer show only their first card? */
        for (size_t i = 0; i < 2; i++) {
            dealCard(deck, dealer->hand, 1);
            for (size_t i = 0; i < numPlayers; i++)
            {
                if (players[i]->status != BROKE) {
                    dealCard(deck, players[i]->hand, 1); /* TODO: Implement blackjack / Naturals */
                }
            }
        }

        for (size_t i = 0; i < numPlayers; i++) {
            if (getValueOfDeck(players[i]->hand) == 21) {
                snprintf(printBuf, BUF_LEN, "%s has BLACKJACK!", players[i]->name);
                players[i]->status = BLACKJACK;
                textDialog(printBuf, sc);
            }
        }
        
        while (!anyPlayersPlaying(players, numPlayers)) {
            for (size_t i = 0; i < numPlayers; i++) {
                if (players[i]->status == PLAYING) {
                    dealDialog(players[i], deck, sc); /* TODO */

                    if (getValueOfDeck(players[i]->hand) == 21) {
                        snprintf(printBuf, BUF_LEN, "%s has 21!", players[i]->name);
                        textDialog(printBuf, sc);
                        players[i]->status = TWENTY_ONE;
                    }

                    if (getValueOfDeck(players[i]->hand) > 21) {
                        snprintf(printBuf, BUF_LEN, "%s BUSTS!", players[i]->name);
                        textDialog(printBuf, sc);
                        players[i]->status = BUST;
                    }
                }
            }
        }
        
        /* Handle Bets and return cards to deck. */
        for (size_t i = 0; i < numPlayers; i++) {
            /* Bust / Loss */
            betHandler(players[i], dealer);

            dealCard(players[i]->hand, deck, players[i]->hand->size);
        }
        
    }

    textDialog("Game Over!", sc);


    deinitScreenWrapper(sc);

    printf("Press any key to continue...\n");
    getchar();

    

    return EXIT_SUCCESS;
}
