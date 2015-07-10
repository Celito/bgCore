//
// Created by Celito on 2015-07-09.
//

#include "MoveBitTo.h"

bool MoveBitTo::is_available() const {
    return false;
}

void MoveBitTo::init(shared_ptr<Player> player) {
    Action::init(player);
    _target = dynamic_pointer_cast<Board>(_target_ref.get_bit());
}

string MoveBitTo::get_description() const {
    return "Choose a board location";
}
