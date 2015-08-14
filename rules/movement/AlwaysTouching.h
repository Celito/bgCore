//
// Created by Celito on 8/14/2015.
//

#ifndef BGCORE_ALWAYSTOUCHING_H
#define BGCORE_ALWAYSTOUCHING_H


#include "MovementSubRule.h"

class AlwaysTouching : public MovementSubRule {
public:
    virtual bool opt_can_be_processed(const shared_ptr<TileOption> &analyzed_option);
};


#endif //BGCORE_ALWAYSTOUCHING_H
