//
// Created by Celito on 2015-08-16.
//

#ifndef BGCORE_CANSTACK_H
#define BGCORE_CANSTACK_H


#include "MovementSubRule.h"

class CanStack : public MovementSubRule {

public:
    CanStack(bool can_stack) : _can_stack(can_stack) { }

    virtual bool opt_can_be_processed(const shared_ptr<TileOption> &analyzed_option) override;

private:
    bool _can_stack = true;
};


#endif //BGCORE_CANSTACK_H
