#include <iostream>
#include <string>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "game.h"

using namespace std;

int main(int argc, char** argv) {
    bool testing = false;
    string t = "-testing";
    if (argc > 1) {
        if (t.compare(argv[1]) == 0) {
            testing = true;
            cout << "Debug The World" << endl;
            cout << "God mode ready\n" << endl;
        }
    }

    Game game;
    game.start(testing);
    
    return 0;
}
