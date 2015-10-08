//
// Created by Celito on 2015-06-30.
//

#include "MultiActions.h"
#include "options/Option.h"
#include "options/ActionOption.h"
#include "../Turn.h"

void MultiActions::add_sub_action(shared_ptr<ActionDef> action)
{
    _sub_actions.push_back(action);
    _can_pre_process = true;
}

string MultiActions::get_description() const
{
    return "Choose your next action";
}

void MultiActions::choose(shared_ptr<Action> action)
{
    ActionDef::choose(action);
    auto action_chosen = dynamic_pointer_cast<ActionOption>(action->get_choose_opt());
    shared_ptr<ActionDef> next_action_def = action_chosen->get_selected_action();

    shared_ptr<Turn> turn = action->get_turn();
    shared_ptr<Action> next_action = make_shared<Action>(turn, next_action_def);

    next_action->init(next_action);

    turn->add_next_action(next_action);
}

void MultiActions::update_options(Action &action)
{
    for (auto sub_action_def : _sub_actions)
    {
        if (sub_action_def->is_available(action.get_turn()->get_player()))
            action.add_option(make_shared<ActionOption>(sub_action_def));
    }
    return;
}

bool MultiActions::is_available(shared_ptr<Player> player)
{
    return true;
}

const shared_ptr<ActionDef> &MultiActions::get_next_action_def(const shared_ptr<Option> &selected_option)
{
    if (shared_ptr<ActionOption> action_option_ptr = dynamic_pointer_cast<ActionOption>(selected_option))
    {
        return action_option_ptr->get_selected_action();
    }
    return ActionDef::get_next_action_def(selected_option);
}
