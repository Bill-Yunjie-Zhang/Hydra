#include <iostream>
#include <string>
#include <string>
#include "game.h"
#include "player.h"
#include "card.h"
#include "head.h"

using namespace std;

int Game::getPlayerNum() {
    return playerNum;
}

int Game::getRoundNum() {
    return roundNum;
}

void Game::setPlayerNum() {
    int num = 0;

    while (num < 2) {
        cout << "How many players?" << endl;
        cin >> num;
        cout << endl;
    }

    playerNum = num;
}

void Game::generateGameDeck() {
    for (int ii = 0; ii < playerNum; ++ii) {
        // jokers
        for (int jj = 0; jj < 2; ++jj) {
            Card card;
            card.setIndex(0);
            card.setRank('J');
            card.setSuit('J');

            gameDeck.deckPushBack(card);
        }

        // rest
        for (int jj = 0; jj < 4; ++jj) {
            for (int kk = 1; kk < 14; ++kk) {
                Card card;
                if (jj == 0) {
                    card.setSuit('H');
                } else if (jj == 1) {
                    card.setSuit('D');
                } else if (jj == 2) {
                    card.setSuit('C');
                } else if (jj == 3){
                    card.setSuit('S');
                }

                if (kk == 1) {
                    card.setIndex(kk);
                    card.setRank('A');
                    gameDeck.deckPushBack(card);
                } else if (kk == 2) {
                    card.setIndex(kk);
                    card.setRank('2');
                    gameDeck.deckPushBack(card);
                } else if (kk == 3) {
                    card.setIndex(kk);
                    card.setRank('3');
                    gameDeck.deckPushBack(card);
                } else if (kk == 4) {
                    card.setIndex(kk);
                    card.setRank('4');
                    gameDeck.deckPushBack(card);
                } else if (kk == 5) {
                    card.setIndex(kk);
                    card.setRank('5');
                    gameDeck.deckPushBack(card);
                } else if (kk == 6) {
                    card.setIndex(kk);
                    card.setRank('6');
                    gameDeck.deckPushBack(card);
                } else if (kk == 7) {
                    card.setIndex(kk);
                    card.setRank('7');
                    gameDeck.deckPushBack(card);
                } else if (kk == 8) {
                    card.setIndex(kk);
                    card.setRank('8');
                    gameDeck.deckPushBack(card);
                } else if (kk == 9) {
                    card.setIndex(kk);
                    card.setRank('9');
                    gameDeck.deckPushBack(card);
                } else if (kk == 10) {
                    card.setIndex(kk);
                    card.setRank('T');
                    gameDeck.deckPushBack(card);
                } else if (kk == 11) {
                    card.setIndex(kk);
                    card.setRank('J');
                    gameDeck.deckPushBack(card);
                } else if (kk == 12) {
                    card.setIndex(kk);
                    card.setRank('Q');
                    gameDeck.deckPushBack(card);
                } else if (kk == 13) {
                    card.setIndex(kk);
                    card.setRank('K');
                    gameDeck.deckPushBack(card);
                }
            }
        }
    
    }

    gameDeck.deckShuffle();
}

void Game::readyPlayers() {
    for (int ii = 1; ii <= playerNum; ++ii) {
        Player player;
        player.setId(ii);
        player.setTotalCards(0);

        for (int jj = 0; jj < 54; jj++) {
            Card tmp;
            tmp.setCard(gameDeck.getDeckBack().getIndex(), gameDeck.getDeckBack().getSuit(), gameDeck.getDeckBack().getRank());
            player.fillStock(tmp);
            gameDeck.deckPopBack();
        }

        players.push_back(player);
    }
}

void Game::generateHeads(int num, Player& unluckyPlayer) {
    for (int ii = 0; ii < num; ++ii) {
        unluckyPlayer.drawCard();
        Head newHead;
        unluckyPlayer.playCard(newHead, true);
        if (heads.size() == 0) {
            newHead.setId(1);
        } else {
            newHead.setId(heads.back().getHeadId() + 1);
        }  
        
        if (newHead.getHeadSuit() == 'J' && newHead.getHeadRank() == 'J' && newHead.getHeadIndex() == 0) {
            newHead.setHeadIndex(2);
            newHead.setHeadRank('2');
        }

        heads.push_back(newHead);
    }
}

void Game::cutHead(int playerId) {
    players[playerId - 1].getHead(heads[0]);
    heads.erase(heads.begin());
}

void Game::showHeads() {
    cout << "Heads:" << endl;
    for (unsigned int ii = 0; ii < heads.size(); ++ii) {
        if (heads[ii].getHeadRank() == 'T') {
            cout << heads[ii].getHeadId() << ": " << 10 << heads[ii].getHeadSuit() << " (" << heads[ii].getHeadSize() << ")" << endl;
        } else {
            cout << heads[ii].getHeadId() << ": " << heads[ii].getHeadRank() << heads[ii].getHeadSuit() << " (" << heads[ii].getHeadSize() << ")" << endl;
        }
    }
    cout << endl;
}

void Game::roundConclusion() {
    // conclusion
    if (players[roundNum - 1].getReserveNum() != 0) {
        players[roundNum - 1].reserveBack();
    }

    // continue Gaming
    // head part
    showHeads();

    // player part
    cout << "Players: " << endl;
    for (unsigned int ii = 0; ii < players.size(); ++ii) {
        cout << "Player " << players[ii].getId() << ": " << players[ii].getTotalCards() << " (" << players[ii].getStockPileNum() << " draw, " << players[ii].getDiscardNum() << " discard)" << endl;
    }

    cout << endl;
}

void Game::start(bool isTesting) {
    cin.exceptions(ios::eofbit|ios::failbit);
    testing = isTesting;
    hasWin = false;
    setPlayerNum();
    generateGameDeck();
    readyPlayers();

    ///////////////////////////////////////////////
    ///////////////// first round /////////////////
    generateHeads(1, players[0]);

    roundNum = 1;

    roundConclusion();

    ///////////////////////////////////////////////
    /////////////////    round    /////////////////
    while(!hasWin) {
        try {
            ++roundNum;
            roundNum %= playerNum;

            if (roundNum == 0) {
                roundNum = playerNum;
            }

            // to start a round
            cout << "Player " << roundNum << ", it is your turn." << endl;
            cout << endl;

            // card the player has to draw for each round
            for (unsigned int jj = 0; jj < heads.size(); ++jj) {
                // display all heads
                showHeads();

                // draw card
                players[roundNum - 1].drawCard();

                // display all user info
                for (unsigned int ii = 0; ii < players.size(); ++ii) {
                    if (players[ii].getId() == roundNum) {
                        cout << "Player " << players[ii].getId() << ": " << players[ii].getTotalCards() << " (" << players[ii].getStockPileNum() << " draw, " << players[ii].getDiscardNum() << " discard)" << " + 1 in hand, " << heads.size() - jj - 1 << " remaining, " << players[ii].getReserveNum() << " in reserve" << endl;
                    } else {
                        cout << "Player " << players[ii].getId() << ": " << players[ii].getTotalCards() << " (" << players[ii].getStockPileNum() << " draw, " << players[ii].getDiscardNum() << " discard)" << endl;
                    }
                }
                cout << endl;

                // // move
                bool headSatisfy = false;
                bool hasAvailableHeads = false;
                bool endTurn = false;
                bool foundHead = false;
                bool hasA = false;
                int headId;

                while (!foundHead && !headSatisfy) {
                    if (players[roundNum - 1].checkHandCard().getRank() == 'T') {
                        cout << "Player " << roundNum << ", you are holding a " << 10 << players[roundNum - 1].checkHandCard().getSuit() << ". Your move? (0 for reserve)" << endl;
                    } else if (players[roundNum - 1].checkHandCard().getSuit() == 'J') {
                        cout << "Player " << roundNum << ", you are holding a " << "Joker" << ". Your move? (0 for reserve)" << endl;                        
                    } else {
                        cout << "Player " << roundNum << ", you are holding a " << players[roundNum - 1].checkHandCard().getRank() << players[roundNum - 1].checkHandCard().getSuit() << ". Your move? (0 for reserve)" << endl;
                    }

                    cin >> headId;
                    cout << endl;

                    //////////////////////////////// for testing mode ////////////////////////////////
                    if (testing) {
                        bool correctRankInput = false;
                        bool isJoker = false;
                        while (!correctRankInput) {
                            string rank;
                            cout << "Card Value? (enter A, J, Q, K, 2 - 10, or Joker)" << endl;
                            cin >> rank;
                            cout << endl;
                            
                            if (rank == "Joker") {
                                players[roundNum - 1].setHandCardRank('J');
                                players[roundNum - 1].setHandCardIndex(0);
                                players[roundNum - 1].setHandCardSuit('J');   
                                correctRankInput = true; 
                                isJoker = true;                        
                            } else {
                                if (rank == "A") {
                                    players[roundNum - 1].setHandCardRank('A');
                                    players[roundNum - 1].setHandCardIndex(1);
                                    correctRankInput = true;                         
                                } else if (rank == "2") {
                                    players[roundNum - 1].setHandCardRank('2');
                                    players[roundNum - 1].setHandCardIndex(2);
                                    correctRankInput = true;                         
                                } else if (rank == "3") {
                                    players[roundNum - 1].setHandCardRank('3');
                                    players[roundNum - 1].setHandCardIndex(3);
                                    correctRankInput = true;                         
                                } else if (rank == "4") {
                                    players[roundNum - 1].setHandCardRank('4');
                                    players[roundNum - 1].setHandCardIndex(4);
                                    correctRankInput = true;                         
                                } else if (rank == "5") {
                                    players[roundNum - 1].setHandCardRank('5');
                                    players[roundNum - 1].setHandCardIndex(5);
                                    correctRankInput = true;                         
                                } else if (rank == "6") {
                                    players[roundNum - 1].setHandCardRank('6');
                                    players[roundNum - 1].setHandCardIndex(6);
                                    correctRankInput = true;                         
                                } else if (rank == "7") {
                                    players[roundNum - 1].setHandCardRank('7');
                                    players[roundNum - 1].setHandCardIndex(7);
                                    correctRankInput = true;                         
                                } else if (rank == "8") {
                                    players[roundNum - 1].setHandCardRank('8');
                                    players[roundNum - 1].setHandCardIndex(8);
                                    correctRankInput = true;                         
                                } else if (rank == "9") {
                                    players[roundNum - 1].setHandCardRank('9');
                                    players[roundNum - 1].setHandCardIndex(9);
                                    correctRankInput = true;                         
                                } else if (rank == "10") {
                                    players[roundNum - 1].setHandCardRank('T');
                                    players[roundNum - 1].setHandCardIndex(10);
                                    correctRankInput = true;                         
                                } else if (rank == "J") {
                                    players[roundNum - 1].setHandCardRank('J');
                                    players[roundNum - 1].setHandCardIndex(11);
                                    correctRankInput = true;                         
                                } else if (rank == "Q") {
                                    players[roundNum - 1].setHandCardRank('Q');
                                    players[roundNum - 1].setHandCardIndex(12);
                                    correctRankInput = true;                         
                                } else if (rank == "K") {
                                    players[roundNum - 1].setHandCardRank('K');
                                    players[roundNum - 1].setHandCardIndex(13);
                                    correctRankInput = true;                         
                                }
                            }
                        }

                        bool correctSuitInput = false;
                        while (!correctSuitInput && !! !isJoker) {
                            char suit;
                            cout << "Suit? (enter S, H, C, or D)" << endl;
                            cin >> suit;
                            cout << endl;
                            if (suit == 'S' || suit == 'H' || suit == 'C' || suit == 'D') {
                                players[roundNum - 1].setHandCardSuit(suit);
                                correctSuitInput = true;
                            }
                        }
                    }

                    // reserve
                    if (heads.size() != 1) {
                        if (headId == 0) {
                            if (players[roundNum - 1].getReserveNum() == 0) {
                                players[roundNum - 1].reserve();
                                break;
                            } else {
                                players[roundNum - 1].swapReserve();
                                continue;
                            }
                        }
                    }

                    for (unsigned int ii = 0; ii < heads.size(); ++ii) {
                        if (heads[ii].getHeadIndex() >= players[roundNum - 1].checkHandCard().getIndex()) {
                            hasAvailableHeads = true;
                        }

                        if (heads[ii].getHeadIndex() == 1) {
                            hasA = true;
                        }
                    }

                    if (!hasAvailableHeads && !hasA && headId == heads[0].getHeadId()) {
                        cout << "headIndex: " << heads[0].getHeadIndex() << endl;
                        cout << "CardIndex: " << players[roundNum - 1].checkHandCard().getIndex() << endl;
                        // cut
                        players[roundNum - 1].playCard(heads[0], false);
                        cutHead(roundNum);
                        generateHeads(2, players[roundNum - 1]);
                        endTurn = true;
                        break;
                    } else if (!hasAvailableHeads && !hasA) {
                        continue;
                    } else {
                        for (unsigned int ii = 0; ii < heads.size(); ++ii) {
                            if (heads[ii].getHeadId() == headId) {
                                foundHead = true;
                                if (heads[ii].getHeadIndex() == 1) {
                                    cout << "headIndex: " << heads[ii].getHeadIndex() << endl;
                                    cout << "CardIndex: " << players[roundNum - 1].checkHandCard().getIndex() << endl;
                                    headSatisfy = true;
                                    players[roundNum - 1].playCard(heads[ii], false);
                                } else if (heads[ii].getHeadIndex() < players[roundNum - 1].checkHandCard().getIndex()) {
                                    cout << "headIndex: " << heads[ii].getHeadIndex() << endl;
                                    cout << "CardIndex: " << players[roundNum - 1].checkHandCard().getIndex() << endl;
                                    headSatisfy = false;
                                } else if (heads[ii].getHeadIndex() == players[roundNum - 1].checkHandCard().getIndex()) {
                                    cout << "headIndex: " << heads[ii].getHeadIndex() << endl;
                                    cout << "CardIndex: " << players[roundNum - 1].checkHandCard().getIndex() << endl;
                                    headSatisfy = true;
                                    players[roundNum - 1].playCard(heads[ii], false);
                                    endTurn = true;
                                } else {
                                    cout << "headIndex: " << heads[ii].getHeadIndex() << endl;
                                    cout << "CardIndex: " << players[roundNum - 1].checkHandCard().getIndex() << endl;
                                    headSatisfy = true;
                                    players[roundNum - 1].playCard(heads[ii], false);
                                }
                            }
                        }
                    }
                }

                if (players[roundNum - 1].getTotalCards() == 0 && players[roundNum - 1].getReserveNum() == 0) {
                    hasWin = true;
                    cout << "Player " << roundNum << " wins!" << endl;
                    return;
                }

                if (endTurn) {
                    break;
                }
            }

            roundConclusion();
        }
        catch (ios::failure &) {
            break;
        }
    }
}
