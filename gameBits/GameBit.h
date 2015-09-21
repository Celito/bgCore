//
// Created by Celito on 2015-05-29.
//


#ifndef BGCORE_GAMEBIT_H
#define BGCORE_GAMEBIT_H

#include <memory>
#include <vector>
#include <map>
#include <boost/signals2.hpp>
#include "attributes/Attribute.h"

using namespace std;

class BgCore;

enum bit_types_e {
    e_bit,
    e_tile,
    e_piece,
    e_piece_set,
    e_board
};

class GameBit {
public:
    GameBit(BgCore &game, string bit_name);

    virtual ~GameBit() {};

    virtual void init() {};

    uint32_t get_unique_id() const;

    Attribute get_attr(string id) const;

    Attribute get_attr(uint32_t id) const;

    void set_attr(string id, uint32_t value);

    uint32_t get_bit_id() const { return _bit_id; }

    const string &get_bit_name() const;

    shared_ptr<GameBit> get_parent() const;

    void set_parent(shared_ptr<GameBit> const& new_parent);

    BgCore &get_game() const { return _game; }

    Attribute get_attr(uint32_t id);

    virtual void receive(shared_ptr<GameBit> bit);

    bool is_empty() const;

    const vector< weak_ptr<GameBit> >& get_children() const;

    bool is_child_of(shared_ptr<GameBit> const &bit) const;

    boost::signals2::connection on_parent_change(boost::signals2::slot<void(GameBit const &)> slot);

protected:
    BgCore &_game;
    uint32_t _unique_id = 0;
    uint32_t _bit_id;
    map<uint32_t, Attribute> _attributes;

    boost::signals2::signal<void(GameBit const &)> _parent_changed;

    virtual void remove(shared_ptr<GameBit> bit);
};


#endif //BGCORE_GAMEBIT_H
