//
// Created by Celito on 2015-06-29.
//

#include "BitReference.h"
#include "../Game.h"

shared_ptr<GameBit> BitReference::get_bit() {
    if(!_player_targeted)
    {
        return _game.get_table_bit(_bit_id);
    }
    if(_curr_player == nullptr)
    {
        throw "Tring to access a bit reference from a not defined player player";
    }
    return _curr_player->get_bit(_bit_id);
}
