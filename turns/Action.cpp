//
// Created by Celito on 2015-06-27.
//

#include "Action.h"

void Action::apply_to(shared_ptr<Player> player) {
    _curr_player = player;
}

const vector<shared_ptr<ActionOption> > &Action::get_options() const {
    return _options;
}
