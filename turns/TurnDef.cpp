//
// Created by Celito on 2015-06-27.
//

#include "TurnDef.h"
#include "Turn.h"
#include "actions/Action.h"
#include "actions/ActionDef.h"
#include "../player/Player.h"

shared_ptr<ActionDef> TurnDef::get_first_action_def() {
    return _action_defs[0];
}

void TurnDef::add_action_def(shared_ptr<ActionDef> action_def) {
    _action_defs.push_back(action_def);
}

shared_ptr<Turn> TurnDef::generate_turn(shared_ptr<Player> player) {
    // create the turn
    shared_ptr<Turn> turn = make_shared<Turn>(player);

    // create the first action
    shared_ptr<ActionDef> first_action_def = get_first_action_def();
    shared_ptr<Action> first_action = make_shared<Action>(turn, first_action_def);

    // initialize it before using it;
    first_action->init();

    // add the first action to the turn queue of next actions;
    turn->add_next_action(first_action);
    return turn;
}
