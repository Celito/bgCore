//
// Created by Celito on 2015-08-16.
//

#ifndef BGCORE_ONEPIECESGROUP_H
#define BGCORE_ONEPIECESGROUP_H


#include "TestableRule.h"

class OnePiecesGroup : public TestableRule {

public:
    OnePiecesGroup(BgCore &game) : TestableRule(game) { }

    virtual bool test();
};


#endif //BGCORE_ONEPIECESGROUP_H
