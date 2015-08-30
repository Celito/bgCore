//
// Created by Celito on 2015-07-20.
//

#ifndef BGCORE_ENABLEMOVEMENTRULE_H
#define BGCORE_ENABLEMOVEMENTRULE_H


#include "../player/Player.h"
#include "TestableRule.h"

class PlayerAttrComparison : public TestableRule {
public:
    PlayerAttrComparison(BgCore &game): TestableRule(game) {}

    virtual bool test();

    void set_tested_attr(string attr);

    void set_bit_type(bit_types_e bit_type);

private:
    bit_types_e _bit_type = e_bit;

    uint32_t _attr_id;
};


#endif //BGCORE_ENABLEMOVEMENTRULE_H
