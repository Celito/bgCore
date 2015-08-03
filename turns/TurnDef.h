//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_TURN_H
#define BGCORE_TURN_H

#include <vector>
#include <memory>

class ActionDef;

using namespace std;

class TurnDef {
public:
    void add_action(shared_ptr<ActionDef>);

    shared_ptr<ActionDef> get_first_action();

private:
    vector<shared_ptr<ActionDef> > _actions;
};


#endif //BGCORE_TURN_H
