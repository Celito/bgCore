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
    BitReference(string bit_id): _bit_id(bit_id) {}

    shared_ptr<GameBit> get_from_player(shared_ptr<Player> player);

    shared_ptr<GameBit> get_from_table(Game const &game);

private:
    string _bit_id;
};


#endif //BGCORE_BITREFERENCE_H
