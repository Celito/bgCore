//
// Created by Celito on 2015-05-29.
//

#include <map>
#include "BitsManager.h"
#include "gameBits/boards/HexBoard.h"

using namespace std;

BitsManager::BitsManager(Game &game) : _game(game) {}

uint32_t BitsManager::register_bit(shared_ptr<GameBit> bit) {
    auto bit_id = bit->get_bit_id();
    auto ref_id = _all_bits[bit_id].size();
    _all_bits[bit_id].push_back(bit);
    return ref_id;
}
