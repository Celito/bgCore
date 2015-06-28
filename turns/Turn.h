//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_TURN_H
#define BGCORE_TURN_H

#include <vector>
#include <memory>

class Action;

using namespace std;

class Turn {
public:
    void add_action(shared_ptr<Action>);

    shared_ptr<Action> get_first_action();

private:
    vector<shared_ptr<Action> > _actions;
};


#endif //BGCORE_TURN_H
