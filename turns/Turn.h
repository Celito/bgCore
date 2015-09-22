//
// Created by Celito on 2015-08-03.
//

#ifndef BGCORE_TURN_H
#define BGCORE_TURN_H

#include <memory>
#include <vector>
#include <queue>

class Player;
class Action;

using namespace std;

class Turn {
public:
    Turn(shared_ptr<Player> player);

    void register_action(shared_ptr<Action> action);

    void add_next_action(shared_ptr<Action> action);

    shared_ptr<Player> get_player();

    shared_ptr<Action> get_next_action();

    shared_ptr<Action> get_action_ptr(Action const &action_ref);

private:
    weak_ptr<Player> _player;

    vector< shared_ptr<Action> > _actions_taken;

    queue< shared_ptr<Action> > _next_actions;
};


#endif //BGCORE_TURN_H
