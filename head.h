#ifndef _HEAD_H__
#define _HEAD_H__

#include "deck.h"
#include "card.h"

using namespace std;

class Head {
    private:
        int id;
        Deck headPile;
    public:
        void setId(int num);

        // add to head
        void headPushBack(Card& playCard);

        // get head info
        int getHeadId();
        int getHeadSize();

        // get head card info
        int getHeadIndex();
        char getHeadRank();
        char getHeadSuit();

        void setHeadIndex(int index);
        void setHeadRank(char rank);

        Card getHeadBack() const;
};

#endif
