//
// Created by Celito on 7/9/2015.
//

#include "BitOption.h"
#include "../../gameBits/GameBit.h"

string BitOption::get_description() {
    return _selected_bit->get_bit_id();
}
