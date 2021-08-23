#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "deck.h"
#include "card.h"
#include "head.h"

using namespace std;

class Player {
    private:
        int id;
        int totalCards;
        Deck stockPile;
        Card handCard;
        Deck discardPile;
        Deck reservePile;
    public:
        void setId(int idNum);
        int getId();

        void setTotalCards(int cardNum);
        void addTotalCards(int cardNum);
        int getTotalCards();

        void fillStock(Card newCard);
        int getStockPileNum();

        void getDiscard();
        int getDiscardNum();

        void drawCard();

        /////////////////////////////// for testing mode ///////////////////////////////
        void setHandCardRank(char rank);
        void setHandCardIndex(int index);
        void setHandCardSuit(char suit);
        ////////////////////////////////////////////////////////////////////////////////
        
        Card checkHandCard() const;

        void reserve();
        void swapReserve();
        void reserveBack(); // put card in reserve back to stockPile
        int getReserveNum();

        void playCard(Head& playHead, bool isHead);

        void getHead(Head& oldestHead);
};

#endif
