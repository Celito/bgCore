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

    uint32_t get_next_unique_id();

    void remove_bit(shared_ptr<GameBit> bit);

    shared_ptr<GameBit> get_bit(uint32_t unique_id);

    shared_ptr<GameBit> get_first_bit(string bit_id);

    //This is a nested map with the first key being the bit id and the second one being the bit refId
    map<uint32_t, shared_ptr<GameBit> > _all_bits;

private:
    Game &_game;

    uint32_t _unique_id = 0;

};




#endif //BGCORE_BITSMANAAGER_H
