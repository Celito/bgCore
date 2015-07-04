//
// Created by Celito on 2015-06-27.
//

#include "Action.h"

void Action::init(shared_ptr<Player> player) {
    _curr_player = player;
}

const vector<shared_ptr<Option> > &Action::get_options() const {
    return _options;
}
