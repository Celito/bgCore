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

TurnsManager::TurnsManager(Game &game) : _game(game) {
    _current_player_id = 0;
}

void TurnsManager::next_turn() {
    //TODO: change the players order if defined by the game
    cout << "====== PLAYER " << _current_player_id + 1 << " TURN STARTED ========" << endl;
    auto curr_player = _game.get_player(_current_player_id);
    _current_player_id++;
    if(_current_player_id + 1 > _game.get_num_of_players()) _current_player_id = 0;

    //TODO: choose the turn according to the conditions to choose the turn type;
    shared_ptr<TurnDef> turn_def = _turn_definitions[0];

    shared_ptr<ActionDef> curr_action_def = turn_def->get_first_action_def();

    shared_ptr<PlayerController> player_controller = curr_player->get_controller();

    shared_ptr<Turn> curr_turn = turn_def->generate_turn(curr_player);

    while(curr_action_def != nullptr) {
        shared_ptr<Action> action = curr_action_def->generate_action(curr_turn);
        while(curr_action_def->self_resolve()) {
            curr_action_def = curr_action_def->get_next_action().lock();
        }
        if(curr_action_def) {
            player_controller->resolve_action(curr_action_def);
            curr_action_def = curr_action_def->get_next_action().lock();
        }

        curr_turn.get()->register_action(action);
    }

    _match_turns.push_back(curr_turn);
}

void TurnsManager::register_turn_def(shared_ptr<TurnDef> turn) {
    _turn_definitions.push_back(turn);
}
