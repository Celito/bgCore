//
// Created by Celito on 8/19/2015.
//

#include "CustomEvent.h"

void CustomEvent::add_game_change(shared_ptr<GameChange> game_change)
{
    _game_changes.push_back(game_change);
}
