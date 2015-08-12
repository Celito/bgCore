//
// Created by Celito on 2015-06-03.
//

#include <c++/iostream>
#include "TurnsManager.h"
#include "../Game.h"
#include "TurnDef.h"
#include "actions/ActionDef.h"
#include "../player/PlayerController.h"
#include "../player/Player.h"
#include "Turn.h"
#include "State.h"

TurnsManager::TurnsManager(Game &game) : _game(game) {
    _current_player_id = 0;
    _curr_state = make_shared<State>();
}

void TurnsManager::next_turn() {
    //TODO: change the players order if defined by the game
    cout << "====== PLAYER " << _current_player_id + 1 << " TURN STARTED ========" << endl;
    auto curr_player = _game.get_player(_current_player_id);
    _current_player_id++;
    if(_current_player_id + 1 > _game.get_num_of_players()) _current_player_id = 0;

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
}

void TurnsManager::register_turn_def(shared_ptr<TurnDef> turn) {
    _turn_definitions.push_back(turn);
}

const shared_ptr<State> &TurnsManager::get_curr_state() {
    return _curr_state;
}
