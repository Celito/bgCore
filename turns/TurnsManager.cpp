//
// Created by Celito on 2015-06-03.
//

#include <iostream>
#include "TurnsManager.h"
#include "../Game.h"
#include "TurnDef.h"
#include "actions/ActionDef.h"
#include "../player/PlayerController.h"
#include "../player/Player.h"
#include "Turn.h"
#include "State.h"

TurnsManager::TurnsManager(Game &game) : _game(game) {
    _curr_player_id = 0;
    _curr_state = make_shared<State>();
    _curr_round = 1;
}

void TurnsManager::next_turn() {
    //TODO: add the configuration option to allow a player to skip a turn or not

    cout << "====== PLAYER " << _curr_player_id + 1 << " TURN STARTED ========" << endl;
    auto curr_player = _game.get_player(_curr_player_id);
    _curr_player_id++;
    bool round_ended = false;
    if(_curr_player_id + 1 > _game.get_num_of_players()) {
        round_ended = true;
        _curr_player_id = 0;
    }

    //TODO: choose the turn according to the conditions to choose the turn type;
    shared_ptr<TurnDef> turn_def = _turn_definitions[0];

    shared_ptr<PlayerController> player_controller = curr_player->get_controller();

    _curr_turn = turn_def->generate_turn(curr_player);

    while(_curr_action = _curr_turn->get_next_action()) {

        if(!_curr_action->self_resolve()) {
            player_controller->resolve_action(_curr_action);
        }

        _curr_turn->register_action(_curr_action);
    }

    _match_turns.push_back(_curr_turn);
    _turn_changed();

    if(round_ended) {
        _curr_round++;
        _round_changed();
    }
}

void TurnsManager::register_turn_def(shared_ptr<TurnDef> turn) {
    _turn_definitions.push_back(turn);
}

const shared_ptr<State> &TurnsManager::get_curr_state() {
    return _curr_state;
}

boost::signals2::connection TurnsManager::on_round_changed(boost::signals2::slot<void()> slot) {
    return _round_changed.connect(slot);
}

uint32_t TurnsManager::round() {
    return _curr_round;
}

boost::signals2::connection TurnsManager::on_turn_changed(boost::signals2::slot<void()> slot) {
    return _turn_changed.connect(slot);
}
