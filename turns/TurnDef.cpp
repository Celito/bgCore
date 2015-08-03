//
// Created by Celito on 2015-06-27.
//

#include "TurnDef.h"

shared_ptr<ActionDef> TurnDef::get_first_action() {
    return _actions[0];
}

void TurnDef::add_action(shared_ptr<ActionDef> action) {
    _actions.push_back(action);
}
