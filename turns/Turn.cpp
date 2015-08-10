//
// Created by Celito on 2015-08-03.
//

#include "Turn.h"
#include "../player/Player.h"
#include "actions/Action.h"

Turn::Turn(shared_ptr<Player> player) : _player(player) {}

void Turn::register_action(shared_ptr<Action> action) {
    _actions_taken.push_back(action);
}

shared_ptr<Player> Turn::get_player() {
    return _player.lock();
}

void Turn::add_next_action(shared_ptr<Action> action) {
    _next_actions.push(action);
}

shared_ptr<Action> Turn::get_next_action() {
    if(_next_actions.size() == 0) return nullptr;
    shared_ptr<Action> next = _next_actions.front();
    _next_actions.pop();
    return next;
}
