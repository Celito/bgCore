//
// Created by Celito on 2015-05-29.
//

#include <c++/iostream>
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

void GameBit::set_attr(string id, uint32_t value) {
    if(!_game.get_attr()->is_registered(id)) _game.get_attr()->register_id(id);
    _attributes[_game.get_attr()->get_id(id)] = Attribute(value);
}

Attribute GameBit::get_attr(string id) {
    return _attributes[_game.get_attr()->get_id(id)];
}
