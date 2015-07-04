//
// Created by Celito on 5/27/2015.
//

#include <c++/iostream>
#include <algorithm>
#include "Player.h"
#include "../Game.h"
#include "PlayerInterface.h"
#include "../gameBits/PieceSet.h"

using namespace std;

Player::Player(Game &game, unsigned int id) : _game(game), _id(id) {
    _interface = make_shared<PlayerInterface>(*this);
    cout << "Creating the player " << id << endl;
}

void Player::receive(shared_ptr<PieceSet> bit) {
    _possessions.push_back(bit);
}

shared_ptr<GameBit> Player::get_bit(string bit_id) const {
    vector<shared_ptr<GameBit>>::const_iterator it;
    it = find_if(_possessions.begin(), _possessions.end(),
                          [bit_id](shared_ptr<GameBit> const& bit) -> bool { return bit->get_bit_id() == bit_id;});
    return *it;
}