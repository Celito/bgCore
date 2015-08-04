//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_TURNDEF_H
#define BGCORE_TURNDEF_H

#include <vector>
#include <memory>

class ActionDef;
class Turn;
class Player;

using namespace std;

class TurnDef {
public:
    void add_action_def(shared_ptr<ActionDef>);

    shared_ptr<ActionDef> get_first_action_def();

    shared_ptr<Turn> generate_turn(shared_ptr<Player> player);

private:
    vector<shared_ptr<ActionDef> > _action_defs;
};


#endif //BGCORE_TURN_H
