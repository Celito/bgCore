#include <iostream>
#include "BgCore.h"
#include "tui/GameTUI.h"

using namespace std;

int main() {

    BgCore game("Hive.bgrules");
    GameTUI gameTUI(game);
    gameTUI.run();

    cout << "You reached the end of the program" << endl;
    system("pause");

    return 0;
}