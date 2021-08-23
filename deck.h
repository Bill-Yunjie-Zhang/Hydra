#ifndef _DECK_H__
#define _DECK_H__

#include <vector>
#include "card.h"

using namespace std;

class Deck {
    private:
        vector<Card> deck;
    public:
        // add private variables
        void deckPushBack(Card card);
        void deckPopBack();
        void deckShuffle();

        // getting private variables
        int getDeckLength();
        Card getDeckBack() const;
        Card getDeckFront() const;
        Card getFromIndex(int index) const;

        // set back index
        void setBackIndex(int index);
        void setBackRank(char rank);

};

#endif
