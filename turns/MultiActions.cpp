//
// Created by Celito on 2015-06-30.
//

#include "MultiActions.h"
#include <algorithm>
#include "ActionOption.h"

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

void MultiActions::apply_to(shared_ptr<Player> player) {
    Action::apply_to(player);
    for_each(_sub_actions.begin(), _sub_actions.end(), [player, this](shared_ptr<Action> action) -> void{
         action->apply_to(player);
         if(action->is_available()) _options.push_back(make_shared<ActionOption>(action));
    });
}

string MultiActions::get_description() const {
    return "Choose your next action";
}
