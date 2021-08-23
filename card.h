#ifndef _CARD_H__
#define _CARD_H__

using namespace std;

class Card {
    private:
        // 0, J, J for Jokers
        int index; // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
        char suit; // 'J', 'H', 'D', 'C', 'S'
        char rank; // 'J', 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q'', 'K'
    public:
        // setting private variables
        void setIndex(int indexNum);
        void setSuit(char suitChar);
        void setRank(char rankStr);
        void setCard(int indexNum, char suitChar, char rankStr);

        // getting private variables
        int getIndex();
        char getSuit();
        char getRank();
};

#endif
