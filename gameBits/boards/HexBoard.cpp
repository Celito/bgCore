//
// Created by Celito on 2015-05-29.
//

#include <c++/iostream>
#include "HexBoard.h"

using namespace std;

HexBoard::HexBoard(GameManager *game, std::string refId) : GameBit(game, refId){
    cout << "Creating a hex board" << endl;
}
