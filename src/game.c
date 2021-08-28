/* Already included in game.h: "player.h", "ui.h", "io.h" */ 
#include <stdio.h>
#include "game.h"
#include "defs.h"
#include "deck.h"

void betDialog(Player * p, ScreenWrapper * s)
{
    char buf[BUF_LEN + 1] = "";
    snprintf(buf, BUF_LEN, "%s has %u. How much do you want to bet? ", p->name, p->balance);

    unsigned int bet = getNum(s, p->balance, buf);

    p->currentBet = bet;
    p->balance -= bet;
}

void textDialog(char * str, ScreenWrapper * s)
{
    redrawWindowBorders(s->inputWin);
    printCentred(s->inputWin, (getmaxy(s->inputWin) / 2), str);
    getch();
}

void dealDialog(Player * p, Deck * src, ScreenWrapper * s)
{
    char buf[BUF_LEN + 1] = "";
    const char * options[] = {"Hit", "Stand"};
    const char optionChars[] = {'h', 's'};
    
    snprintf(buf, BUF_LEN, "%s has a score of %u. Hit or Stand?", p->name, getValueOfDeck(p->hand));
    
    if (getInput(s->inputWin, buf, options, optionChars) == 0) {
        dealCard(src, p->hand, 1);
    } else {
        p->status = STAND;
    }
}

void betHandler(Player * p, Player * dealer)
{
    WinState outcome = LOSS; /* By default. */

    unsigned int dealerVal = getValueOfDeck(dealer->hand);
    unsigned int playerVal = getValueOfDeck(p->hand);


    if (playerVal > 21) {
        outcome = LOSS;
    } else if (dealerVal < 21) {
        if (playerVal > dealerVal) {
            outcome = WIN;
        } else if (playerVal < dealerVal) {
            outcome = LOSS;
        } else {
            outcome = PUSH;
        }
    } else if (dealerVal > 21) {
        outcome = WIN;        
    } else if (dealerVal == 21) {
        if (p->status == BLACKJACK) {
            outcome = PUSH;
        }
    }
    /* TODO */
}