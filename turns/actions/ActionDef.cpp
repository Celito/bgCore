//
// Created by Celito on 2015-06-27.
//

#include "ActionDef.h"
#include "../../gameBits/BitReference.h"
#include "../Turn.h"

void ActionDef::init(Action & action) {
    _curr_player = action.get_turn()->get_player();
    for (auto item : _bit_refs) {
        item.second->set_curr_player(_curr_player);
        const shared_ptr<GameBit> &bit = item.second->get_bit();
        if(bit) action.add_req_bit(item.first, bit);
    }
    update_options(action);
    if(action.get_options().size() == 0) throw new exception();
}

void ActionDef::choose(shared_ptr<Action> action) { }

boost::signals2::connection ActionDef::on_action_taken(boost::signals2::slot<void(shared_ptr<Action>)> slot) {
    return _action_taken.connect(slot);
}
