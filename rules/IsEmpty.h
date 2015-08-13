//
// Created by Celito on 8/13/2015.
//

#ifndef BGCORE_ISEMPTY_H
#define BGCORE_ISEMPTY_H


#include "TestableRule.h"

class IsEmpty : public TestableRule {
public:
    IsEmpty(Game &game) : TestableRule(game) { }

    virtual bool test();
};


#endif //BGCORE_ISEMPTY_H
