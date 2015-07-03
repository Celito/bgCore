//
// Created by Celito on 2015-06-27.
//

#include <c++/iostream>
#include "PlayerTUI.h"
#include "../turns/Action.h"

void PlayerTUI::resolve_action(shared_ptr<Action> action) {
    auto options = action->get_options();
    cout << "player controller received " << (action->is_available() ? "a valid" :  "an invalid") << " action with " <<
            options.size() << " options" <<  endl;
    action->is_available();
}
