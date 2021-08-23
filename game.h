#ifndef _GAME_H__
#define _GAME_H__

#include <vector>
#include <iostream>
#include "player.h"
#include "deck.h"
#include "head.h"

using namespace std;

class Game {
    private:
        bool testing;
        bool hasWin;
        int playerNum;
        int roundNum;
        Deck gameDeck; // all cards for the game
        vector<Player> players;
        vector<Head> heads;
    public:
        void setPlayerNum();
        void generateGameDeck();
        void readyPlayers();
        void showHeads();

        void cutHead(int playerId);
        void roundConclusion();
        void forTest();

        void start(bool isTesting);
        void generateHeads(int num, Player& unluckyPlayer);

        int getPlayerNum();
        int getRoundNum();
};

#endif
