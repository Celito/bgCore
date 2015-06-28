//
// Created by Celito on 2015-06-27.
//

#include "Turn.h"

shared_ptr<Action> Turn::get_first_action() {
    return _actions[0];
}

void Turn::add_action(shared_ptr<Action> action) {
    _actions.push_back(action);
}
