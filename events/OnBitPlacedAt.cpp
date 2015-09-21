//
// Created by Celito on 9/21/2015.
//

#include <iostream>
#include "OnBitPlacedAt.h"
#include "../gameBits/GameBit.h"

OnBitPlacedAt::OnBitPlacedAt(shared_ptr<GameBit> tracked_bit, shared_ptr<GameBit> target_parent) :
        _tracked_bit(tracked_bit), _target_parent(target_parent){
    tracked_bit->on_parent_change(boost::bind(&OnBitPlacedAt::on_tracked_bit_change_parent, this, _1));
}

void OnBitPlacedAt::on_tracked_bit_change_parent(GameBit const &bit) {
    if(_tracked_bit.expired()) throw new exception();
    if(_target_parent.expired()) throw new exception();
    auto target_parent_ptr = _target_parent.lock();
    if(_tracked_bit.lock()->is_child_of(target_parent_ptr))
    {
        cout << "Reached an \"OnBitPlaced\" event" << endl;
    }
}
