//
// Created by Celito on 2015-05-29.
//

#include <map>
#include "BitsManager.h"

using namespace std;

BitsManager::BitsManager(BgCore &game) : _game(game) {
    // '0' bits id is an empty id:
    _registered_bits_ids_names.push_back("None");
}

void BitsManager::register_bit(shared_ptr<GameBit> bit) {
    uint32_t bit_unique_id = bit->get_unique_id();
    _all_bits[bit_unique_id] = bit;
}

uint32_t BitsManager::get_next_unique_id() {
    _unique_id++;
    return _unique_id;
}

void BitsManager::remove_bit(shared_ptr<GameBit> bit) {
    _all_bits.erase(bit->get_unique_id());
}

shared_ptr<GameBit> BitsManager::get_bit(uint32_t unique_id) {
    return _all_bits[unique_id];
}

shared_ptr<GameBit> BitsManager::get_first_bit(string bit_name) {
    uint32_t bit_id = get_bit_id_by_name(bit_name);
    for (auto bit_entry : _all_bits) {
        if(bit_entry.second != nullptr && bit_entry.second->get_bit_id() == bit_id)
            return bit_entry.second;
    }
    return nullptr;
}

uint32_t BitsManager::get_bit_id_by_name(string bit_name) {
    for (uint32_t i = 0; i < _registered_bits_ids_names.size(); ++i) {
        if(_registered_bits_ids_names[i] == bit_name) return i;
    }
    _registered_bits_ids_names.push_back(bit_name);
    return _registered_bits_ids_names.size() - 1;
}

const string &BitsManager::get_bit_name_by_id(uint32_t bit_id) const {
    if(bit_id > _registered_bits_ids_names.size() - 1 ) throw new exception();
    return _registered_bits_ids_names[bit_id];
}

vector<shared_ptr<GameBit>> BitsManager::get_table_bits() {
    vector<shared_ptr<GameBit>> ret;
    for (auto bit_entry : _all_bits)
    {
        shared_ptr<GameBit> &bit_ptr = bit_entry.second;
        if(bit_ptr->get_parent() == nullptr)
        {
            ret.push_back(bit_ptr);
        }
    }
    return ret;
}
