//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_BITSMANAGER_H
#define BGCORE_BITSMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "gameBits/GameBit.h"
#include "Game.h"

using namespace std;

class Game;

class BitsManager {

public:
    BitsManager(Game & game);

    void register_bit(shared_ptr<GameBit> bit);

    // id for the instance of each bit'
    uint32_t get_next_unique_id();

    // id for bits with the same name and group of bits
    uint32_t get_bit_id_by_name(string bit_name);

    const string & get_bit_name_by_id(uint32_t bit_id) const;

    void remove_bit(shared_ptr<GameBit> bit);

    shared_ptr<GameBit> get_bit(uint32_t unique_id);

    shared_ptr<GameBit> get_first_bit(string bit_name);

    //This is a nested map with the first key being the bit id and the second one being the bit refId
    map<uint32_t, shared_ptr<GameBit> > _all_bits;

private:
    Game &_game;

    vector<string> _registered_bits_ids_names;

    uint32_t _unique_id = 0;

};




#endif //BGCORE_BITSMANAAGER_H
