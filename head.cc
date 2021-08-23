#include <iostream>
#include "head.h"

using namespace std;

void Head::headPushBack(Card& playCard) {
    headPile.deckPushBack(playCard);
}

void Head::setId(int num) {
    id = num;
}

int Head::getHeadId() {
    return id;
}

int Head::getHeadIndex() {
    return headPile.getDeckBack().getIndex();
}

char Head::getHeadRank() {
    return headPile.getDeckBack().getRank();
}

char Head::getHeadSuit() {
    return headPile.getDeckBack().getSuit();
}

int Head::getHeadSize() {
    return headPile.getDeckLength();
}

Card Head::getHeadBack() const {
    return headPile.getDeckBack();
}

void Head::setHeadIndex(int index) {
    headPile.setBackIndex(index);
}

void Head::setHeadRank(char rank) {
    headPile.setBackRank(rank);
}
