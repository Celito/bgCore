//
// Created by Celito on 2015-07-20.
//

#include "PlayerAttrComparison.h"
#include "../Game.h"
#include "../turns/actions/ActionDef.h"

bool PlayerAttrComparison::test(GameBit const &bit) {
    return _player->get_attr(_attr_id).get_value() == bit.get_attr(_attr_id).get_value();
}

void PlayerAttrComparison::set_tested_attr(string attr) {
    _attr_id = _game.get_attr().get()->register_id(attr);
}
