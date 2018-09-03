//
// Created by Celito on 5/27/2015.
//

#include <iostream>
#include <string.h>
#include <algorithm>
#include <utility>
#include "Player.h"
#include "../BgCore.h"
#include "../turns/State.h"
#include "PlayerInterface.h"
#include "PlayerController.h"
#include "../BitsManager.h"

Player::Player(BgCore &game, uint8_t id) : _id(id), GameBit(game, string("Player") + to_string(id))  {
    _interface = make_shared<PlayerInterface>(*this);
    cout << "Creating the player " << (uint16_t)id << endl;
}

shared_ptr<GameBit> Player::get_first_bit_by_name(string bit_name) const {
    const vector<weak_ptr<GameBit>> &children = _game.curr_state()->get_children(_unique_id);
    uint32_t bit_id = _game.bits_manager()->get_bit_id_by_name(std::move(bit_name));
    for (const auto &child_w : children) {
        if(!child_w.expired() && child_w.lock()->get_bit_id() == bit_id)
            return child_w.lock();
    }
    return nullptr;
}

void Player::set_controller(shared_ptr<PlayerController> controller) {
    _controller = std::move(controller);
    _controller->set_interface(_interface);
}
