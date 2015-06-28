#include <iostream>
#include "Game.h"
#include "tui/GameTUI.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Game game;
    GameTUI gameTUI(game);
    gameTUI.run();

    system("pause");

    return 0;
}