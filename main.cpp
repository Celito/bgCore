#include <iostream>
#include "BgCore.h"
#include "tui/GameTUI.h"

using namespace std;

int main() {

    BgCore game;
    if(game.loadManual("Hive.bgrules"))
    {
        GameTUI gameTUI(game);
        gameTUI.run();
    }
    else
    {
        cout << "Error loading the rules files" << endl;
    }

    cout << "You reached the end of the program" << endl;
    system("pause");

    return 0;
}