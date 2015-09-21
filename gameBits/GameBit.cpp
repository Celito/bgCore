//
// Created by Celito on 2015-05-29.
//

#include <iostream>
#include "GameBit.h"
#include "../BgCore.h"
#include "../BitsManager.h"
#include "../player/Player.h"
#include "../turns/State.h"
#include "attributes/AttrManager.h"

using namespace std;

GameBit::GameBit(BgCore &game, string bit_name) : _game(game) {
    _unique_id = _game.bits_manager()->get_next_unique_id();
    _bit_id = _game.bits_manager()->get_bit_id_by_name(bit_name);
}

uint32_t GameBit::get_unique_id() const {
    return _unique_id;
}

void GameBit::set_attr(string id, uint32_t value) {
    if(!_game.attr_manager()->is_registered(id)) _game.attr_manager()->register_id(id);
    _attributes[_game.attr_manager()->get_id(id)] = Attribute(value);
}

Attribute GameBit::get_attr(string id) const {
    return get_attr(_game.attr_manager()->get_id(id));
}

Attribute GameBit::get_attr(uint32_t id) const {
    return _attributes.at(id);
}

shared_ptr<GameBit> GameBit::get_parent() const {
    return _game.curr_state()->get_parent(get_unique_id());
}

Attribute GameBit::get_attr(uint32_t id) {
    return _attributes[id];
}

void GameBit::receive(shared_ptr<GameBit> bit) {
    bit->set_parent(_game.bits_manager()->get_bit(_unique_id));
}

void GameBit::set_parent(shared_ptr<GameBit> const &new_parent) {
    _game.curr_state()->transfer(_unique_id, new_parent);
    _parent_changed(*this);
}

bool GameBit::is_empty() const {
    return get_children().size() == 0;
}

const vector<weak_ptr<GameBit> > &GameBit::get_children() const {
    return _game.curr_state()->get_children(_unique_id);
}

void GameBit::remove(shared_ptr<GameBit> bit) {
    _game.curr_state()->remove_from_parent(_unique_id, bit);
}

const string &GameBit::get_bit_name() const {
    return _game.bits_manager()->get_bit_name_by_id(_bit_id);
}

boost::signals2::connection GameBit::on_parent_change(boost::signals2::slot<void(GameBit const &)> slot) {
    return _parent_changed.connect(slot);
}

bool GameBit::is_child_of(shared_ptr<GameBit> const &bit) const {
    auto parent = get_parent();
    return parent == bit || parent != nullptr && parent->is_child_of(bit);
}
