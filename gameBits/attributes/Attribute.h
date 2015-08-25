//
// Created by Celito on 7/17/2015.
//

#ifndef BGCORE_ATTRIBUTE_H
#define BGCORE_ATTRIBUTE_H

#include <stdint.h>

class Attribute {
public:
    Attribute(uint32_t value) : _value(value) {}
    Attribute() : _value(0) {}

    uint32_t get_value() const { return _value; }
private:
    uint32_t _value;
};


#endif //BGCORE_ATTRIBUTE_H
