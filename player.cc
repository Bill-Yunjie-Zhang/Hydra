#include <iostream>
#include <string>
#include "player.h"

using namespace std;

void Player::setId(int idNum) {
    id = idNum;
}

void Player::setTotalCards(int num) {
    totalCards = num;
}

void Player::addTotalCards(int num) {
    totalCards += num;
}

void Player::fillStock(Card newCard) {
    ++totalCards;
    stockPile.deckPushBack(newCard);
}

void Player::drawCard() {
    if (stockPile.getDeckLength() == 0) {
        getDiscard();
        if (stockPile.getDeckLength() == 0 && reservePile.getDeckLength() != 0) {
            reserveBack();
        }
    }
    handCard.setCard(stockPile.getDeckBack().getIndex(), stockPile.getDeckBack().getSuit(), stockPile.getDeckBack().getRank());
    if (handCard.getSuit() == 'J') {
        handCard.setCard(0, 'J', 'J');
    } 
    --totalCards;
    stockPile.deckPopBack();
}

void Player::reserve() {
    reservePile.deckPushBack(handCard);
}

void Player::swapReserve() {
    Card tmp;
    tmp.setCard(reservePile.getDeckBack().getIndex(), reservePile.getDeckBack().getSuit(), reservePile.getDeckBack().getRank());
    reservePile.deckPopBack();
    reserve();
    handCard.setCard(tmp.getIndex(), tmp.getSuit(), tmp.getRank());
}

void Player::reserveBack() {
    Card tmp;
    tmp.setCard(reservePile.getDeckBack().getIndex(), reservePile.getDeckBack().getSuit(), reservePile.getDeckBack().getRank());
    reservePile.deckPopBack();
    fillStock(tmp);
}

void Player::setHandCardRank(char rank) {
    handCard.setRank(rank);
}
void Player::setHandCardIndex(int index) {
    handCard.setIndex(index);
}
void Player::setHandCardSuit(char suit) {
    handCard.setSuit(suit);
}

void Player::playCard(Head& playHead, bool isHead) {
    if (handCard.getSuit() == 'J' && !isHead) {
        int index;
        string rankStr;
        bool exception = true;
        char rank;
        
        while (exception) {
            cout << "Joker value?" << endl;
            cin >> rankStr;
            cout << endl;
            
            if (rankStr == "10") {
                index = 10;
                exception = false;
                rank = 'T';
            } else if (rankStr == "J") {
                index = 11;
                exception = false;
                rank = 'J';
            } else if (rankStr == "Q") {
                index = 12;
                exception = false;
                rank = 'Q';
            } else if (rankStr == "K") {
                index = 13;
                exception = false;
                rank = 'K';
            } else if (rankStr == "A") {
                index = 1;
                exception = false;
                rank = 'A';
            } else {
                if (rankStr.length() == 1) {
                    rank = rankStr[0];
                    index = rank - '0'; 
                    if (index > 0 && index < 10) {
                        exception = false;
                    }  
                }
            }    
        }
        
        handCard.setIndex(index);
        handCard.setRank(rank);
    }
    playHead.headPushBack(handCard);
}

void Player::getHead(Head& oldestHead) {
    for (int ii = 0; ii < oldestHead.getHeadSize(); ++ii) {
        ++totalCards;
        discardPile.deckPushBack(oldestHead.getHeadBack());
    }
}

void Player::getDiscard() {
    discardPile.deckShuffle();
    int length = discardPile.getDeckLength();
    for (int ii = 0; ii < length; ++ii) {
        fillStock(discardPile.getDeckBack());
        --totalCards;
        discardPile.deckPopBack();
    }
}

int Player::getDiscardNum() {
    return discardPile.getDeckLength();
}

int Player::getId() {
    return id;
}

int Player::getTotalCards() {
    return totalCards;
}

int Player::getStockPileNum() {
    return stockPile.getDeckLength();
}

Card Player::checkHandCard() const {
    return handCard;
}

int Player::getReserveNum() {
    return reservePile.getDeckLength();
}