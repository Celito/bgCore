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

using namespace std;

class Game;

class BitsManager {

public:
    BitsManager(Game & game);

    template<class T>
    shared_ptr<T> create_bit(string bit_id);

    uint32_t register_bit(shared_ptr<GameBit> bit);

    //This is a nested map with the first key being the bit id and the second one being the bit refId
    map<string, vector< shared_ptr<GameBit> > > _all_bits;

private:
    Game &_game;

};

template<class T>
shared_ptr<T> BitsManager::create_bit(string bit_id) {
    static_assert((is_base_of<GameBit, T>::value),"Type T of create_bit must be a GameBit");
    auto gameBit = make_shared<T>(_game, bit_id);
    static_cast<GameBit*>(gameBit.get())->set_ref_id(register_bit(gameBit));
    return gameBit;
}




#endif //BGCORE_BITSMANAAGER_H
