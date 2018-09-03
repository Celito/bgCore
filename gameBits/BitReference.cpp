//
// Created by Celito on 2015-06-29.
//

#include "BitReference.h"

shared_ptr<GameBit> BitReference::get_bit() {
    if(!_player_targeted)
    {
        return _game.get_table_bit(_bit_id);
    }
    if(_curr_player == nullptr)
    {
        throw "Trying to access a bit reference from a not defined player player";
    }
    return _curr_player->get_first_bit_by_name(_bit_id);
}

shared_ptr<GameBit> BitReference::get_bit(const shared_ptr<Player> &player) {
    set_curr_player(player);
    return get_bit();
}
