//
// Created by Celito on 2015-05-29.
//

#include <c++/iostream>
#include "GameBit.h"

GameBit::GameBit(GameManager *game, std::string refId) {
    _game = game;
    _refId = refId;
    std::cout << "created the bit '" << refId << "'" << std::endl;
}
