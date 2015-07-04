//
// Created by Celito on 2015-06-29.
//

#include "BitReference.h"
#include "../Game.h"

shared_ptr<GameBit> BitReference::get_from_player(shared_ptr<Player> player) {
    return player->get_bit(_bit_id);
}

shared_ptr<GameBit> BitReference::get_from_table(Game const &game) {
    return game.get_table_bit(_bit_id);
}