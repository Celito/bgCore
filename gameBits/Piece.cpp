//
// Created by Celito on 2015-05-29.
//

#include "Piece.h"
#include <iostream>
#include "../player/Player.h"
#include "../rules/Rule.h"
#include "../rules/PlayerAttrComparison.h"
#include "../rules/MovementFilterRule.h"

using namespace std;

Piece::Piece(Game &game, string refId) : GameBit(game, refId){}

bool Piece::available_for_movement(shared_ptr<Player> player) const {
//    bool ret = true;
//    for (auto rule : _availability_for_movement) {
//        rule->set_curr_player(player);
//        rule->add_req_bit(e_piece, player);
//        ret &= rule->test();
//    }
//    return ret;
    return false;
}
