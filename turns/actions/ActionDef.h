//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_ACTIONDEF_H
#define BGCORE_ACTIONDEF_H

#include <boost/signals2.hpp>
#include "Action.h"

using namespace std;

class Option;

class Player;

class GameBit;

class BitReference;

class Turn;

class ActionDef
{
public:

    ActionDef(BgCore &game) : _game(game) { }

    void init_act_instance(Action &action);

    virtual void update_options(Action &action) = 0;

    virtual bool is_available(shared_ptr<Player> player) = 0;

    virtual string get_description() const = 0;

    virtual void process_choice(shared_ptr<Action> action);

    virtual action_type_e get_type() { return e_not_defined; }

    bool can_pre_process() const { return _can_pre_process; }

    boost::signals2::connection on_action_taken(boost::signals2::slot<void(shared_ptr<Action>)> slot);

    virtual const shared_ptr<ActionDef> &get_next_action_def(const shared_ptr<Option> &selected_option);

    virtual void init_by_option(shared_ptr<Action> action, shared_ptr<Option> selected_option);

protected:
    map<bit_types_e, shared_ptr<BitReference> > _bit_refs;
    shared_ptr<Player> _curr_player;
    shared_ptr<ActionDef> _static_next_action;
    bool _can_pre_process = false;

    boost::signals2::signal<void(shared_ptr<Action>)> _action_taken;

    BgCore &_game;
};


#endif //BGCORE_ACTION_H
