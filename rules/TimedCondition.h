//
// Created by Celito on 8/13/2015.
//

#ifndef BGCORE_CONDITION_H
#define BGCORE_CONDITION_H

#include <iostream>
#include <boost/signals2.hpp>
#include "TestableRule.h"
#include "../events/EventManager.h"

class BgCore;

using namespace std;

class TimedCondition {
public:
    TimedCondition(BgCore & game);

    TimedCondition(BgCore & game, common_events_t check_on);

    void add_condition(shared_ptr<TestableRule> condition);

    boost::signals2::connection on_satisfied(boost::signals2::slot<void()> slot);

    boost::signals2::connection on_unsatisfied(boost::signals2::slot<void()> slot);

private:
    vector<shared_ptr<TestableRule>> _conditions;

    common_events_t _check_on;

    BgCore &_game;

    boost::signals2::signal<void()> _satisfied;
    boost::signals2::signal<void()> _unsatisfied;

    bool _curr_satisfied = false;
};


#endif //BGCORE_CONDITION_H
