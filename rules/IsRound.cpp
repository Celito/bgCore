//
// Created by Celito on 8/14/2015.
//

#include "IsRound.h"
#include "../Game.h"
#include "../turns/TurnsManager.h"

bool IsRound::test() {
    uint32_t round = _game.turns_manager()->round();
    _required_bits.clear();
    return round > _min_round;
}

void IsRound::is_bigger_then(uint32_t round) {
    _min_round = round;
}
