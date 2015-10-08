//
// Created by Celito on 7/31/2015.
//

#ifndef BGCORE_MOVEMENTFILTERRULE_H
#define BGCORE_MOVEMENTFILTERRULE_H

#include <stdint.h>
#include <vector>
#include <memory>
#include "Rule.h"
#include "movement/MovementSubRule.h"

class Tile;
class TileOption;
class Piece;
class Option;
class MovementSubRule;

using namespace std;

class MovementFilterRule : public Rule {
public:
    virtual void filter_positions(vector<shared_ptr<Option> > &options, shared_ptr<Tile> initial_tile,
                          const shared_ptr<Piece> &moving_piece);

    void set_max_steps(uint32_t value);

    void set_min_steps(uint32_t value);

    void add_movement_sub_rule(const shared_ptr<MovementSubRule> &sub_rule);

private:
    uint32_t _max_steps = UINT32_MAX;
    uint32_t _min_steps = 0;
    bool _restricted_steps = false;

    vector<shared_ptr<MovementSubRule>> _movement_sub_rules;

    bool opt_can_be_processed(const shared_ptr<TileOption> &opt) const;
};


#endif //BGCORE_MOVEMENTFILTERRULE_H
