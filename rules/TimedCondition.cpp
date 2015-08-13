//
// Created by Celito on 8/13/2015.
//

#include "TimedCondition.h"
#include "../Game.h"
#include "../turns/TurnsManager.h"

TimedCondition::TimedCondition(Game &game): _game(game) {
    //every game turn the condition check to see if it was satisfied or unsatisfied;
    _game.turns_manager()->on_round_changed([this](uint32_t turn){
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
