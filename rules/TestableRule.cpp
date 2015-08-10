//
// Created by Celito on 8/10/2015.
//

#include "TestableRule.h"

void TestableRule::add_req_bit(bit_types_e bit_type, shared_ptr<GameBit> req_bit) {
    _required_bits[bit_type] = req_bit;
}
