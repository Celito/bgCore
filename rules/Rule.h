//
// Created by Celito on 7/17/2015.
//

#ifndef BGCORE_RULE_H
#define BGCORE_RULE_H

#include <string>
#include <vector>

enum rule_usage_t {
    e_not_specified,
    e_movement_rule,
    e_placement_rule,
    e_movement_enable_rule
};

using namespace std;

class Rule {
public:
    virtual ~Rule() {};

    rule_usage_t get_usage() const {
        return _usage;
    }

    void set_usage(rule_usage_t usage) {
        _usage = usage;
    }

    void add_applicable_bit(string bit_id) {
        _applicable_bits.push_back(bit_id);
    }

    const vector<string> &get_applicable_bits_ids() const {
        return _applicable_bits;
    }

private:
    rule_usage_t _usage = e_not_specified;

    // list of bit_ids of the applicable bits that this rule will be used on
    vector<string> _applicable_bits;
};


#endif //BGCORE_RULE_H
