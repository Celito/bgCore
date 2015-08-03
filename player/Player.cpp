//
// Created by Celito on 5/27/2015.
//

#include <c++/iostream>
#include <algorithm>
#include "Player.h"
#include "../Game.h"
#include "PlayerInterface.h"
#include "PlayerController.h"

using namespace std;

Player::Player(Game &game, unsigned int id) : _game(game), _id(id) {
    _interface = make_shared<PlayerInterface>(*this);
    cout << "Creating the player " << id << endl;
}

shared_ptr<GameBit> Player::get_bit(string bit_id) const {
    vector<weak_ptr<GameBit>>::const_iterator it;
    it = find_if(_bits.begin(), _bits.end(),
                          [bit_id](weak_ptr<GameBit> const& bit) -> bool { return bit.lock()->get_bit_id() == bit_id;});
    return it->expired() ? nullptr : it->lock();
}

void Player::set_controller(shared_ptr<PlayerController> controller) {
    _controller = controller;
}

void Player::set_attr(string id, uint32_t value) {
    _attributes[_game.get_attr()->register_id(id)] = Attribute(value);
}

Attribute Player::get_attr(uint32_t id) {
    return _attributes[id];
}
