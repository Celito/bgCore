//
// Created by Celito on 8/17/2015.
//

#ifndef BGCORE_EVENTMANAGER_H
#define BGCORE_EVENTMANAGER_H

#include "../Game.h"

enum common_events_t {
    e_turn_changed,
    e_round_changed
};

class EventManager {
public:
    EventManager(Game &game) : _game(game) {}

    void on_common_event(common_events_t event, boost::signals2::slot<void()> slot);

private:
    Game &_game;
};


#endif //BGCORE_EVENTMANAGER_H
