//
// Created by Celito on 7/10/2015.
//

#include "BitHolder.h"
#include <algorithm>
#include "../Game.h"

void BitHolder::receive(shared_ptr<GameBit> bit) {
    if(bit->get_parent().get() == this) return;
    if(bit->get_parent()) bit->get_parent()->remove(bit);
    else bit->get_game().remove(bit);
    bit->set_parent(this);
    _bits.push_back(bit);
}

bool BitHolder::is_empty() const {
    return _bits.size() == 0;
}

void BitHolder::remove(shared_ptr<GameBit> bit) {
    _bits.erase(std::remove_if(
            _bits.begin(),_bits.end(),
            [&bit](weak_ptr<GameBit> &b) -> bool { return b.expired()? false : b.lock() == bit; }), _bits.end());
}
