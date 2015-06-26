//
// Created by Celito on 5/27/2015.
//

#include <c++/iostream>
#include "Player.h"
#include "PlayerInterface.h"
#include "gameBits/PieceSet.h"

using namespace std;

Player::Player(unsigned int id) {
    _id = id;
    _interface = make_shared<PlayerInterface>(shared_ptr<Player>(this));
    cout << "Creating the player " << id << endl;
}

void Player::receive(shared_ptr<PieceSet> bit) {
    _possessions[bit->get_unique_id()] = bit;
}
