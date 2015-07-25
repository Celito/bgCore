//
// Created by Celito on 2015-05-29.
//


#ifndef BGCORE_GAMEBIT_H
#define BGCORE_GAMEBIT_H

#include <memory>
#include <map>
#include "attributes/Attribute.h"

using namespace std;

class Game;
class BitHolder;

class GameBit {
public:
    GameBit(Game &game, string bit_id);

    virtual ~GameBit() {};

    uint32_t get_unique_id() const;

    Attribute get_attr(string id) const;

    Attribute get_attr(uint32_t id) const;

    void set_attr(string id, uint32_t value);

    void set_ref_id(const uint32_t ref_id) { if(_ref_id == 0) _ref_id = ref_id; }

    const string &get_bit_id() const { return _bit_id; }

    shared_ptr<BitHolder> get_parent() const;

    void set_parent(BitHolder *parent) { _parent = parent; }

    Game &get_game() const { return _game; }

protected:
    Game &_game;
    uint32_t _ref_id = 0;
    string _bit_id;
    map<uint32_t, Attribute> _attributes;

private:
    BitHolder * _parent;
};


#endif //BGCORE_GAMEBIT_H
