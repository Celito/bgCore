//
// Created by Celito on 2015-06-27.
//

#include "ActionDef.h"
#include "../../gameBits/BitReference.h"

void ActionDef::init(shared_ptr<Player> player) {
    _curr_player = player;
    for (auto item : _bit_refs) {
        item.second->set_curr_player(_curr_player);
        _required_bits[item.first] = item.second->get_bit();
    }
    update_options();
}

const vector<shared_ptr<Option> > &ActionDef::get_options() const {
    return _options;
}

boost::signals2::connection ActionDef::on_option_taken(boost::signals2::slot<void(shared_ptr<Option>)> slot) {
    return _option_taken.connect(slot);
}

void ActionDef::choose(shared_ptr<Option> option) {
    _option_taken(option);
}

bool ActionDef::is_available() const {
    return _options.size() > 0;
}

void ActionDef::concat_action(shared_ptr<ActionDef> other_action) {
    _next_action = other_action;
    _option_taken.connect([this](shared_ptr<Option> opt){
        for (auto bit_pair : _selected_bits) {
            if(!_next_action.expired() && !bit_pair.second.expired())
                _next_action.lock()->set_required_bit(bit_pair.first, bit_pair.second.lock());
        }
    });
}

void ActionDef::set_required_bit(required_bit_t bit_type, shared_ptr<GameBit> bit) {
    _required_bits[bit_type] = bit;
}
