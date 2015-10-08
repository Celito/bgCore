//
// Created by Celito on 8/14/2015.
//

#ifndef BGCORE_JUMPOVERNEIGHBOURS_H
#define BGCORE_JUMPOVERNEIGHBOURS_H


#include "MovementFilterRule.h"

class JumpOverNeighbours : public MovementFilterRule {

public:
    virtual void filter_positions(vector<shared_ptr<Option> > &options, shared_ptr<Tile> initial_tile,
                          const shared_ptr<Piece> &moving_piece) override;
};


#endif //BGCORE_JUMPOVERNEIGHBOURS_H
