//
// Created by Celito on 5/27/2015.
//

#include <c++/iostream>
#include <algorithm>
#include "Player.h"
#include "../Game.h"
#include "../turns/State.h"
#include "PlayerInterface.h"
#include "PlayerController.h"

Player::Player(Game &game, uint32_t id) : _id(id), GameBit(game, string("Player") + to_string(id))  {
    _interface = make_shared<PlayerInterface>(*this);
    cout << "Creating the player " << id << endl;
}

shared_ptr<GameBit> Player::get_bit(string bit_id) const {
    const vector<weak_ptr<GameBit>> &children = _game.curr_state()->get_children(_unique_id);
    for (auto child_w : children) {
        if(child_w.expired() && child_w.lock()->get_bit_id() == bit_id);
        return child_w.lock();
    }
    return nullptr;
}

void Player::set_controller(shared_ptr<PlayerController> controller) {
    _controller = controller;
    _controller->set_interface(_interface);
}
