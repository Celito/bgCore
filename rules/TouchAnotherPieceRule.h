//
// Created by Celito on 8/11/2015.
//

#ifndef BGCORE_TOUCHANOTHERPIECERULE_H
#define BGCORE_TOUCHANOTHERPIECERULE_H

#include <vector>
#include "TestableRule.h"

class TouchAnotherPieceRule : public TestableRule {
public:
    TouchAnotherPieceRule(Game &game): TestableRule(game) {}

    virtual bool test();

    void add_piece_matching_player_attr(string attr);

private:
    bool _do_not_touch = true;

    vector<uint32_t> _matching_attrs_player;
};


#endif //BGCORE_TOUCHANOTHERPIECERULE_H
