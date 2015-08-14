//
// Created by Celito on 8/14/2015.
//

#ifndef BGCORE_ISROUND_H
#define BGCORE_ISROUND_H


#include "TestableRule.h"

class IsRound : public TestableRule {
public:
    IsRound(Game &game) : TestableRule(game) { }

    void is_bigger_then(uint32_t round);

    virtual bool test();

private:
    uint32_t _min_round = 0;
};


#endif //BGCORE_ISROUND_H
