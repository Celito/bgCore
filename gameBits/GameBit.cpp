//
// Created by Celito on 2015-05-29.
//

#include <c++/iostream>
#include <string>
#include "GameBit.h"
#include "../Game.h"
#include "../BitsManager.h"

using namespace std;

GameBit::GameBit(Game &game, string bit_id) : _game(game), _parent(nullptr) {
    _bit_id = bit_id;
}

string GameBit::get_unique_id() const {
    return _bit_id + "_" + to_string(_ref_id);
}
