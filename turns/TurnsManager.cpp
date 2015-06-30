//
// Created by Celito on 2015-06-03.
//

#include "TurnsManager.h"
#include "Turn.h"
#include "Action.h"
#include "../player/Player.h"
#include "../player/PlayerController.h"
#include "../Game.h"

TurnsManager::TurnsManager(Game &game) : _game(game) {
    _current_player_id = 0;
}

void TurnsManager::start_turn() {
    //TODO: change the players order if defined by the game

    auto curr_player = _game.get_player(_current_player_id);
    _current_player_id++;
    if(_current_player_id > _game.get_num_of_players()) _current_player_id = 0;

    //TODO: choose the turn according to the conditions to choose the turn type;
    shared_ptr<Turn> turn = _possible_turns[0];

    shared_ptr<Action> action = turn->get_first_action();

    shared_ptr<PlayerController> controller = curr_player->get_controller();

    action->apply_to(curr_player);

    //TODO: if the first action is not available, the throw an error, because the player have no valid actions to take;
    controller->resolve_action(action);

}

void TurnsManager::register_turn(shared_ptr<Turn> turn) {
    _possible_turns.push_back(turn);
}
