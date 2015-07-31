//
// Created by Celito on 7/31/2015.
//

#ifndef BGCORE_MOVEMENTFILTERRULE_H
#define BGCORE_MOVEMENTFILTERRULE_H


#include "../gameBits/boards/Tile.h"
#include "../turns/options/TileOption.h"

class MovementFilterRule {
public:
    void filter_positions(vector<shared_ptr<Option> > &options, shared_ptr<Tile> initial_tile);
};


#endif //BGCORE_MOVEMENTFILTERRULE_H
