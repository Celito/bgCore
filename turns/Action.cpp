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

boost::signals2::connection Action::on_option_taken(boost::signals2::slot<void(shared_ptr<Option>)> slot) {
    return _option_taken.connect(slot);
}

void Action::choose(shared_ptr<Option> option) {
    _option_taken(option);
}
