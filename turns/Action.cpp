//
// Created by Celito on 2015-06-27.
//

#include "Action.h"

void Action::init(shared_ptr<Player> player) {
    _curr_player = player;
    for (auto item : _bit_refs) {
        item.second->set_curr_player(_curr_player);
        _required_bits[item.first] = item.second->get_bit();
    }
    update_options();
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

bool Action::is_available() const {
    return _options.size() > 0;
}

void Action::concat_action(shared_ptr<Action> other_action) {
    _next_action = other_action;
    _option_taken.connect([this](shared_ptr<Option> opt){
        for (auto bit_pair : _selected_bits) {
            if(!_next_action.expired())
                _next_action.lock()->set_required_bit(bit_pair.first, bit_pair.second);
        }
    });
}
