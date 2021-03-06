//
// Created by Celito on 2015-06-03.
//

#include <iostream>
#include "TurnsManager.h"
#include "../BgCore.h"
#include "TurnDef.h"
#include "actions/ActionDef.h"
#include "../player/PlayerController.h"
#include "../player/Player.h"
#include "Turn.h"
#include "State.h"

TurnsManager::TurnsManager(BgCore &game) : _game(game) {
    _killed = false;
    _curr_player_id = 0;
    _curr_state = make_shared<State>(game);
    _curr_round = 1;
}

void TurnsManager::next_turn() {

    cout << "====== PLAYER " << _curr_player_id + 1 << " TURN STARTED ========" << endl;
    auto curr_player = _game.get_player(_curr_player_id);

    shared_ptr<TurnDef> turn_def = _player_turn_defs[_curr_player_id][0];

    shared_ptr<PlayerController> player_controller = curr_player->get_controller();

    _curr_turn = turn_def->generate_turn(curr_player);

    while(_curr_action = _curr_turn->get_next_action()) {

        // ask for the game interface for the player choice;
        if(!_curr_action->self_resolve()) {
            player_controller->resolve_action(_curr_action);
        }

        // if the game was killed during the choice the function should just return for now;
        if(_killed)
        {
            return;
        }

        _curr_turn->register_action(_curr_action);
    }

    _match_turns.push_back(_curr_turn);
    _turn_changed();

    _curr_player_id++;
    bool round_ended = false;
    if(_curr_player_id + 1 > _game.get_num_of_players()) {
        round_ended = true;
        _curr_player_id = 0;
    }

    if(round_ended) {
        _curr_round++;
        _round_changed();
    }
}

void TurnsManager::register_player_turn_def(uint8_t player_id, shared_ptr<TurnDef> turn) {
    _player_turn_defs[player_id].push_back(turn);
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

void TurnsManager::kill()
{
    _killed = true;
}
