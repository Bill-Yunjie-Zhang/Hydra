#include <algorithm>
#include <random>
#include <chrono>
#include "deck.h"

#include <iostream>

using namespace std;

void Deck::deckPushBack(Card card) {
    deck.push_back(card);
}

void Deck::deckPopBack() {
    deck.pop_back();
}

void Deck::deckShuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

int Deck::getDeckLength() {
    return deck.size();
}

Card Deck::getDeckBack() const {
    return deck.back();
}

Card Deck::getDeckFront() const {
    return deck.front();
}

Card Deck::getFromIndex(int index) const {
    return deck[index];
}

void Deck::setBackIndex(int index) {
    deck[deck.size() - 1].setIndex(index);
}

void Deck::setBackRank(char rank) {
    deck[deck.size() - 1].setRank(rank);
}
