//
// Created by Celito on 8/13/2015.
//

#include "TimedCondition.h"
#include "../turns/TurnsManager.h"

TimedCondition::TimedCondition(Game &game):TimedCondition(game, e_round_changed) {}

TimedCondition::TimedCondition(Game &game, common_events_t check_on) : _game(game), _check_on(check_on) {
    //every event [check_on] the condition check to see if it was satisfied or unsatisfied;
    _game.event_manager()->on_common_event(_check_on, [this](){
        bool is_satisfied = true;
        for (auto condition : _conditions) {
            if(!condition->test()){
                is_satisfied = false;
                break;
            }
        }
        if(_curr_satisfied != is_satisfied){
            _curr_satisfied = is_satisfied;
            if(is_satisfied){
                _satisfied();
            }
            else {
                _unsatisfied();
            }
        }
    });
    _curr_satisfied = false;
}

void TimedCondition::add_condition(shared_ptr<TestableRule> condition) {
    _conditions.push_back(condition);
}

boost::signals2::connection TimedCondition::on_satisfied(boost::signals2::slot<void()> slot) {
    return _satisfied.connect(slot);
}

boost::signals2::connection TimedCondition::on_unsatisfied(boost::signals2::slot<void()> slot) {
    return _unsatisfied.connect(slot);
}
