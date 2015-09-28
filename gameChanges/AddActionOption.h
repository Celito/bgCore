//
// Created by Celito on 9/25/2015.
//

#ifndef BGCORE_ADDACTIONOPTION_H
#define BGCORE_ADDACTIONOPTION_H


#include "GameChange.h"

class ActionDef;
class MultiActions;

class AddActionOption : public GameChange {
public:
    AddActionOption(shared_ptr<MultiActions> target_multi_action, shared_ptr<ActionDef> added_action, BgCore &core) :
            GameChange(core), _target_multi_action(target_multi_action), _added_action(added_action) {}

    virtual void apply();

private:

    weak_ptr<MultiActions> _target_multi_action;
    shared_ptr<ActionDef> _added_action;
};


#endif //BGCORE_ADDACTIONOPTION_H
