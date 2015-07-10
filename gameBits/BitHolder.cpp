//
// Created by Celito on 7/10/2015.
//

#include "BitHolder.h"
#include "GameBit.h"
#include <algorithm>

void BitHolder::receive(shared_ptr<GameBit> bit) {
    if(&bit->get_parent() == this) return;
    bit->get_parent().remove(bit);
    bit->_parent = *this;
    _bits.push_back(bit);
}

bool BitHolder::is_empty() const {
    return _bits.size() == 0;
}

void BitHolder::remove(shared_ptr<GameBit> bit) {
    _bits.erase(find(_bits.begin(),_bits.end(),bit));
}
