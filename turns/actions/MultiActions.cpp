//
// Created by Celito on 2015-06-30.
//

#include "MultiActions.h"
#include "Action.h"
#include "options/Option.h"
#include "options/ActionOption.h"
#include "../Turn.h"

void MultiActions::add_sub_action(shared_ptr<ActionDef> action) {
    _sub_actions.push_back(action);
}

string MultiActions::get_description() const {
    return "Choose your next action";
}

void MultiActions::choose(Action &action) {
    ActionDef::choose(action);
    auto action_chosen = dynamic_pointer_cast<ActionOption>(action.get_choose_opt());
    shared_ptr<ActionDef> next_action_def = action_chosen->get_selected_action();

    shared_ptr<Action> next_action = make_shared<Action>(action.get_turn(), next_action_def);

    action.get_turn()->add_next_action(next_action);
}

void MultiActions::update_options(Action &action) {
    for (auto sub_action : _sub_actions) {
        action.add_option(make_shared<ActionOption>(sub_action));
    }
    return;
}
