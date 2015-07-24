//
// Created by Celito on 2015-05-29.
//

#include <map>
#include <algorithm>
#include "BitsManager.h"

using namespace std;

BitsManager::BitsManager(Game &game) : _game(game) {}



uint32_t BitsManager::register_bit(shared_ptr<GameBit> bit) {
    auto bit_id = bit->get_bit_id();
    auto ref_id = _all_bits[bit_id].size();
    _all_bits[bit_id].push_back(bit);
    return ref_id;
}

void BitsManager::remove_bit(shared_ptr<GameBit> bit) {
    vector<shared_ptr<GameBit>> &vec = _all_bits[bit->get_bit_id()];
    vec.erase(std::remove(vec.begin(), vec.end(), bit), vec.end());
    if(vec.size() == 0) {
        _all_bits.erase(bit->get_bit_id());
    }
}
