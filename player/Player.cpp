//
// Created by Celito on 5/27/2015.
//

#include <c++/iostream>
#include <algorithm>
#include "Player.h"
#include "../Game.h"
#include "PlayerInterface.h"
#include "PlayerController.h"
#include "../gameBits/PieceSet.h"

using namespace std;

Player::Player(Game &game, unsigned int id) : _game(game), _id(id) {
    _interface = make_shared<PlayerInterface>(*this);
    cout << "Creating the player " << id << endl;
}

shared_ptr<GameBit> Player::get_bit(string bit_id) const {
    vector<shared_ptr<GameBit>>::const_iterator it;
    it = find_if(_bits.begin(), _bits.end(),
                          [bit_id](shared_ptr<GameBit> const& bit) -> bool { return bit->get_bit_id() == bit_id;});
    return *it;
}

void Player::set_controller(shared_ptr<PlayerController> controller) {
    _controller = controller;
    _controller->set_interface(get_interface());
}
