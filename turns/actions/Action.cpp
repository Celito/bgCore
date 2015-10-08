//
// Created by Celito on 2015-08-03.
//

#include "Action.h"
#include "ActionDef.h"
#include "../Turn.h"

Action::Action(const weak_ptr<Turn> &turn, const weak_ptr<ActionDef> &definition)
        : _turn(turn), _definition(definition)
{
    _initialized = false;
}

const vector<shared_ptr<Option> > &Action::get_options() const
{
    return _options;
}

bool Action::self_resolve()
{
    if (!_initialized) throw new exception();
    if (_options.size() == 0) throw new exception();

    if (_can_self_resolve && _options.size() == 1)
    {
        choose(_options[0]);
        return true;
    }
    return false;
}

void Action::choose(shared_ptr<Option> option)
{
    // The _choose_option must be null to make sure this action was not already taken
    if (!_choose_option.expired()) throw new exception();
    if (_self_ptr.expired()) throw new exception();
    _choose_option = option;
    _definition.lock()->choose(_self_ptr.lock());
    _option_taken(option);
}

string Action::get_description() const
{
    if (_definition.expired()) throw new exception();
    return _definition.lock()->get_description();
}

action_type_e Action::get_type() const
{
    if (_definition.expired()) throw new exception();
    return _definition.lock()->get_type();
}

shared_ptr<GameBit> Action::get_req_bit(bit_types_e bit_type)
{
    return _required_bits.count(bit_type) ? _required_bits[bit_type].lock() : nullptr;
}

void Action::add_req_bit(bit_types_e bit_type, shared_ptr<GameBit> ptr)
{
    _required_bits[bit_type] = ptr;
}

void Action::add_option(shared_ptr<Option> option)
{
    _options.push_back(option);
    shared_ptr<ActionDef> def_ptr = _definition.lock();
    if (def_ptr->can_pre_process())
    {
        shared_ptr<ActionDef> next_action_def_ptr = def_ptr.get()->get_next_action_def(option);
        if(next_action_def_ptr != nullptr)
        {
            shared_ptr<Action> next_action = make_shared<Action>(_turn, next_action_def_ptr);
            next_action_def_ptr->init_by_option(next_action, option);
        }
    }
}

shared_ptr<Turn> Action::get_turn() const
{
    return _turn.lock();
}

shared_ptr<Option> Action::get_choose_opt() const
{
    return _choose_option.lock();
}

boost::signals2::connection Action::on_option_taken(boost::signals2::slot<void(shared_ptr<Option>)> slot)
{
    return _option_taken.connect(slot);
}

void Action::init(const shared_ptr<Action> &self_ptr)
{
    if (_initialized) throw new exception();
    _definition.lock()->init_act_instance(*this);
    _initialized = true;
    _self_ptr = self_ptr;
}

void Action::set_self_resolvable(bool self_resolvable)
{
    _can_self_resolve = self_resolvable;
}
