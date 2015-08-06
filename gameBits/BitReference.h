//
// Created by Celito on 2015-06-29.
//

#ifndef BGCORE_BITREFERENCE_H
#define BGCORE_BITREFERENCE_H

#include <string>
#include "GameBit.h"
#include "../player/Player.h"
#include "../BitsManager.h"

using namespace std;

/**
 * A reference to a bit of the game that could belong to the table or the current player, it could be a a specific bit
 * with it id identified or the first bit available on that bits container;
 */
class BitReference {
public:
    BitReference(string bit_id, Game &game, bool player_targeted = false):
            _bit_id(bit_id), _game(game), _player_targeted(player_targeted) {}

    shared_ptr<GameBit> get_bit(const shared_ptr<Player> &player);

    shared_ptr<GameBit> get_bit();

    void set_curr_player(const shared_ptr<Player> &player) {
        BitReference::_curr_player = player;
    }

private:
    string _bit_id;
    bool _player_targeted;
    shared_ptr<Player> _curr_player;
    Game &_game;
};


#endif //BGCORE_BITREFERENCE_H
