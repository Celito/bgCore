//
// Created by Celito on 2015-08-03.
//

#ifndef BGCORE_ACTION_H
#define BGCORE_ACTION_H

#include <memory>
#include <vector>
#include <map>
#include <boost/signals2.hpp>
#include "../../gameBits/GameBit.h"

class Turn;
class ActionDef;
class Option;

using namespace std;

enum action_type_e {
    e_action_type_not_defined,
    e_action_type_choose_tile,
    e_action_type_place_piece_on_board,
    e_action_type_move_piece_on_board
};

class Action {

public:
    Action(const weak_ptr<Turn> &turn, const weak_ptr<ActionDef> &definition);

    void init(const shared_ptr<Action> &self_ptr);

    bool self_resolve();

    void choose(shared_ptr<Option> option);

    const vector< shared_ptr<Option> >& get_options() const;

    string get_description() const;

    action_type_e get_type() const;

    shared_ptr<GameBit> get_req_bit(bit_types_e bit_type);

    void add_req_bit(bit_types_e bit_type, shared_ptr<GameBit> req_bit);

    void add_option(shared_ptr<Option> option);

    shared_ptr<Turn> get_turn() const;

    shared_ptr<Option> get_choose_opt() const;

    void set_self_resolvable(bool self_resolvable);

    boost::signals2::connection on_option_taken(boost::signals2::slot<void(shared_ptr<Option>)> slot);

private:
    bool _initialized;
    bool _can_self_resolve = true;
    weak_ptr<Turn> _turn;
    weak_ptr<ActionDef> _definition;
    weak_ptr<Option> _choose_option;
    vector< shared_ptr <Option> > _options;
    map<bit_types_e, weak_ptr<GameBit> > _required_bits;

    boost::signals2::signal<void(shared_ptr<Option>)> _option_taken;
    weak_ptr<Action> _self_ptr;
};


#endif //BGCORE_ACTION_H
