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

void MultiActions::update_options(Action &action)
{
    shared_ptr<Player> player = action.get_turn()->get_player();
    Player * player_ptr = player.get();
    for (auto sub_action_def : _sub_actions)
    {
        ActionDef * sub_action_def_ptr = sub_action_def.get();
        bool is_available =  sub_action_def_ptr->is_available(player);
        if (is_available)
            action.add_option(make_shared<ActionOption>(sub_action_def));
    }
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
