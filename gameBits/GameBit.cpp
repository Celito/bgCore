//
// Created by Celito on 2015-05-29.
//

#include <c++/iostream>
#include "GameBit.h"
#include "../Game.h"
#include "../BitsManager.h"
#include "../player/Player.h"

using namespace std;

GameBit::GameBit(Game &game, string bit_id) : _game(game), _parent(nullptr) {
    _bit_id = bit_id;
}

uint32_t GameBit::get_unique_id() const {
    return _ref_id;
}

void GameBit::set_attr(string id, uint32_t value) {
    if(!_game.get_attr()->is_registered(id)) _game.get_attr()->register_id(id);
    _attributes[_game.get_attr()->get_id(id)] = Attribute(value);
}

Attribute GameBit::get_attr(string id) const {
    return get_attr(_game.get_attr()->get_id(id));
}

Attribute GameBit::get_attr(uint32_t id) const {
    return _attributes.at(id);
}

shared_ptr<BitHolder> GameBit::get_parent() const {
    if(GameBit* bit = dynamic_cast<GameBit *>(_parent)){
        return (shared_ptr<BitHolder>)dynamic_pointer_cast<BitHolder>(_game.bits_manager()->get_bit(bit->get_unique_id()));
    } else if(Player* player = dynamic_cast<Player *>(_parent)) {
        return (shared_ptr<BitHolder>)dynamic_pointer_cast<BitHolder>(_game.get_player(player->get_id() - 1));
    }
    return nullptr ;
}
