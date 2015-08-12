//
// Created by Celito on 2015-05-29.
//

#include <map>
#include "BitsManager.h"

using namespace std;

BitsManager::BitsManager(Game &game) : _game(game) {}



void BitsManager::register_bit(shared_ptr<GameBit> bit) {
    bit->set_ref_id(_unique_id);
    _unique_id++;
    uint32_t bit_id = bit->get_unique_id();
    _all_bits[bit_id] = bit;
}

void BitsManager::remove_bit(shared_ptr<GameBit> bit) {
    _all_bits.erase(bit->get_unique_id());
}

shared_ptr<GameBit> BitsManager::get_bit(uint32_t unique_id) {
    return _all_bits[unique_id];
}

shared_ptr<GameBit> BitsManager::get_first_bit(string bit_id) {
    for (auto bit_entry : _all_bits) {
        if(bit_entry.second != nullptr && bit_entry.second->get_bit_id() == bit_id)
            return bit_entry.second;
    }
    return nullptr;
}
