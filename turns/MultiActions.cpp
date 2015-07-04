//
// Created by Celito on 2015-06-30.
//

#include "MultiActions.h"
#include <algorithm>
#include "options/Option.h"
#include "options/ActionOption.h"

bool MultiActions::is_available() const {
    bool available = false;
    for(auto it = _sub_actions.cbegin(); it != _sub_actions.cend(); it++)
    {
        available = available || it->get()->is_available();
    }
    return available;
}

void MultiActions::add_sub_action(shared_ptr<Action> action) {
    _sub_actions.push_back(action);
}

void MultiActions::init(shared_ptr<Player> player) {
    Action::init(player);
    for_each(_sub_actions.begin(), _sub_actions.end(), [player, this](shared_ptr<Action> action) -> void{
        action->init(player);
         if(action->is_available()) _options.push_back(make_shared<ActionOption>(action));
    });
}

string MultiActions::get_description() const {
    return "Choose your next action";
}

void MultiActions::choose(shared_ptr<Option> option) {
    shared_ptr<ActionOption> action_choosed = dynamic_pointer_cast<ActionOption>(option);
    shared_ptr<Action> next_action = action_choosed->get_selected_action();
    set_next_action(next_action);
}

bool MultiActions::self_resolve() {
    if(_options.size() == 1)
    {
        choose(_options[0]);
        return true;
    }
    return Action::self_resolve();
}
