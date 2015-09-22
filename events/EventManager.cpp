//
// Created by Celito on 8/17/2015.
//

#include "EventManager.h"
#include "../turns/TurnsManager.h"

void EventManager::on_common_event(common_events_t common_event_type, boost::signals2::slot<void()> slot) {
    switch (common_event_type){

        case e_turn_changed:
            _game.turns_manager()->on_turn_changed(slot);
            break;
        case e_round_changed:
            _game.turns_manager()->on_round_changed(slot);
            break;
        default:
            throw new exception();
    }
}

void EventManager::add_custom_event(shared_ptr<CustomEvent> event) {
    _custom_event.push_back(event);
}
