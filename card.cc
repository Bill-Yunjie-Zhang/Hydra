#include "card.h"

using namespace std;

// setting private variables
void Card::setIndex(int indexNum) {
    index = indexNum;
}

void Card::setSuit(char suitChar) {
    suit = suitChar;
}

void Card::setRank(char rankStr) {
    rank = rankStr;
}

void Card::setCard(int indexNum, char suitChar, char rankStr) {
    setIndex(indexNum);
    setSuit(suitChar);
    setRank(rankStr);
}

// getting private variables
int Card::getIndex() {
    return index;
}

char Card::getSuit() {
    return suit;
}

char Card::getRank() {
    return rank;
}
