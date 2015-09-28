//
// Created by Celito on 9/25/2015.
//

#include <iostream>
#include "AddActionOption.h"
#include "../turns/actions/MultiActions.h"

void AddActionOption::apply() {
    GameChange::apply();
    if(_target_multi_action.expired()) throw new exception();
    _target_multi_action.lock()->add_sub_action(_added_action);
}
