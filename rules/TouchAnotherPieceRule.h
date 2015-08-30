//
// Created by Celito on 8/11/2015.
//

#ifndef BGCORE_TOUCHANOTHERPIECERULE_H
#define BGCORE_TOUCHANOTHERPIECERULE_H

#include <vector>
#include "TestableRule.h"

class TouchAnotherPieceRule : public TestableRule {
public:
    TouchAnotherPieceRule(BgCore &game): TestableRule(game) {}

    virtual bool test();

    void add_compared_player_attr(string attr, bool have_to_match);

    void set_reverse(bool do_not_touch) { _do_not_touch = do_not_touch; }

private:
    bool _do_not_touch = false;

    vector<pair<uint32_t, bool>> _compared_attrs_player;
};


#endif //BGCORE_TOUCHANOTHERPIECERULE_H
