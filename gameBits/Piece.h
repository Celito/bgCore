//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_PIECE_H
#define BGCORE_PIECE_H

#include <vector>
#include "GameBit.h"

class Player;
class MovementFilterRule;
class TestableRule;

class Piece : public GameBit {
public:
    Piece(Game &game, std::string refId);

    bool available_for_movement(shared_ptr<Player> player) const;

    void add_movement_availability_rule(shared_ptr<TestableRule> rule){
        _availability_for_movement.push_back(rule);
    }

    void add_movement_rule(shared_ptr<MovementFilterRule> rule) {
        _movement_rules.push_back(rule);
    }

    const vector< shared_ptr<MovementFilterRule> > &get_movement_rules() { return _movement_rules; }

    const vector< shared_ptr<TestableRule> > &get_availability_for_movement_rules() { return _availability_for_movement; }

private:
    vector< shared_ptr<TestableRule> > _availability_for_movement;

    vector< shared_ptr<MovementFilterRule> > _movement_rules;
};


#endif //BGCORE_PIECE_H
