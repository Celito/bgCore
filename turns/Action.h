//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_ACTION_H
#define BGCORE_ACTION_H

#include "../player/Player.h"
#include "../gameBits/BitReference.h"

using namespace std;

class Action {
public:
    virtual void apply_to(shared_ptr<Player> player);

    virtual bool is_available() = 0;

protected:
    vector<BitReference> _references;
    shared_ptr<Player> _curr_player;
};


#endif //BGCORE_ACTION_H
