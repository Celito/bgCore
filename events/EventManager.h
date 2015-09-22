//
// Created by Celito on 8/17/2015.
//

#ifndef BGCORE_EVENTMANAGER_H
#define BGCORE_EVENTMANAGER_H

#include "../BgCore.h"

class CustomEvent;

enum common_events_t {
    e_turn_changed,
    e_round_changed
};

class EventManager {
public:
    EventManager(BgCore &game) : _game(game) {}

    void on_common_event(common_events_t common_event_type, boost::signals2::slot<void()> slot);

    void add_custom_event(shared_ptr<CustomEvent> event);

private:
    BgCore &_game;

    vector<shared_ptr<CustomEvent>> _custom_event;
};


#endif //BGCORE_EVENTMANAGER_H
