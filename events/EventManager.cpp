//
// Created by Celito on 8/17/2015.
//

#include "EventManager.h"
#include "../turns/TurnsManager.h"

void EventManager::on_common_event(common_events_t event, boost::signals2::slot<void()> slot) {
    switch (event){

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
