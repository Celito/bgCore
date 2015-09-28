//
// Created by Celito on 8/19/2015.
//

#ifndef BGCORE_CUSTOMEVENT_H
#define BGCORE_CUSTOMEVENT_H

#include <vector>
#include <memory>
#include "../gameChanges/GameChange.h"

using namespace std;

class CustomEvent {
//TODO: Deal in all the event with the reverse of the event;
public:
    void add_game_change(shared_ptr<GameChange> game_change);

protected:
    vector<shared_ptr<GameChange>> _game_changes;
};


#endif //BGCORE_CUSTOMEVENT_H
