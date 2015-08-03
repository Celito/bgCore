//
// Created by Celito on 7/31/2015.
//

#ifndef BGCORE_MOVEMENTFILTERRULE_H
#define BGCORE_MOVEMENTFILTERRULE_H


#include "../gameBits/boards/Tile.h"
#include "../turns/actions/options/TileOption.h"

class MovementFilterRule {
public:
    void filter_positions(vector<shared_ptr<Option> > &options, shared_ptr<Tile> initial_tile);

    void set_max_steps(uint32_t value);

    void set_min_steps(uint32_t value);

private:
    uint32_t _max_steps = UINT32_MAX;
    uint32_t _min_steps = 0;
    bool _restricted_steps = false;
};


#endif //BGCORE_MOVEMENTFILTERRULE_H
