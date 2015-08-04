//
// Created by Celito on 2015-06-27.
//

#include "TurnDef.h"
#include "Turn.h"
#include "../player/Player.h"

shared_ptr<ActionDef> TurnDef::get_first_action_def() {
    return _action_defs[0];
}

void TurnDef::add_action_def(shared_ptr<ActionDef> action) {
    _action_defs.push_back(action);
}

shared_ptr<Turn> TurnDef::generate_turn(shared_ptr<Player> player) {
    shared_ptr<Turn> turn = make_shared<Turn>(player);
    return turn;
}
