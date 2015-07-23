//
// Created by Celito on 2015-05-29.
//

#include <iostream>
#include "Piece.h"

using namespace std;

Piece::Piece(Game &game, string refId) : GameBit(game, refId){}

bool Piece::available_for_movement(shared_ptr<Player> player) const {
    bool ret = true;
    for (auto rule : _availability_for_movement) {
        rule->set_curr_player(player);
        ret &= rule->test(*this);
    }
    return ret;
}
