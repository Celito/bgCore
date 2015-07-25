#include <iostream>
#include "Game.h"
#include "tui/GameTUI.h"

using namespace std;

int main() {

    Game game;
    GameTUI gameTUI(game);
    gameTUI.run();

    cout << "You reached the end of the program" << endl;
    system("pause");

    return 0;
}