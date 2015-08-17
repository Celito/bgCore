//
// Created by Celito on 2015-07-20.
//

#include "PlayerAttrComparison.h"
#include "../Game.h"
#include "../turns/actions/ActionDef.h"
#include "../gameBits/attributes/AttrManager.h"


void PlayerAttrComparison::set_tested_attr(string attr) {
    _attr_id = _game.attr_manager()->register_id(attr);
}

bool PlayerAttrComparison::test() {
    if(_player.expired()) throw new exception();
    if(_required_bits.count(_bit_type) == 0) throw new exception();
    if(_required_bits[_bit_type].expired()) throw new exception();
    shared_ptr<GameBit> bit = (shared_ptr<GameBit>)dynamic_pointer_cast<GameBit>(_required_bits[_bit_type].lock());
    if(bit == nullptr) return false;

    shared_ptr<Player> player_ptr = _player.lock();
    uint32_t player_attr = player_ptr->get_attr(_attr_id).get_value();
    uint32_t bit_attr = bit->get_attr(_attr_id).get_value();

    _required_bits.clear();

    return player_attr == bit_attr;
}

void PlayerAttrComparison::set_bit_type(bit_types_e bit_type) {
    _bit_type = bit_type;
}
