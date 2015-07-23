//
// Created by Celito on 2015-06-03.
//

#include <c++/iostream>
#include "TurnsManager.h"
#include "Turn.h"
#include "Action.h"
#include "../player/PlayerController.h"

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
    shared_ptr<Turn> turn = _possible_turns[0];

    shared_ptr<Action> curr_action = turn->get_first_action();

    shared_ptr<PlayerController> controller = curr_player->get_controller();

    while(curr_action != nullptr) {
        curr_action->init(curr_player);
        while(curr_action->self_resolve()) {
            curr_action = curr_action->get_next_action().lock();
        }
        if(curr_action) {
            controller->resolve_action(curr_action);
            curr_action = curr_action->get_next_action().lock();
        }
    }
}

void TurnsManager::register_turn(shared_ptr<Turn> turn) {
    _possible_turns.push_back(turn);
}
