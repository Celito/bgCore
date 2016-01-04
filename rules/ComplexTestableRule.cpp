//
// Created by Celito on 10/16/2015.
//

#include "ComplexTestableRule.h"

void ComplexTestableRule::concat_rule(const shared_ptr<TestableRule> &sub_rule)
{
    concat_rule(sub_rule, false, true);
}

void ComplexTestableRule::concat_rule(const shared_ptr<TestableRule> &sub_rule, bool negate, bool and_or)
{
    sub_rule_t new_sub_rule_struct;
    new_sub_rule_struct.rule = sub_rule;
    new_sub_rule_struct.negate = negate;
    new_sub_rule_struct.and_or = and_or;
    _sub_rules.push_back(new_sub_rule_struct);
}

bool ComplexTestableRule::test()
{
    bool result = false;
    for (int i = 0; i < _sub_rules.size(); ++i)
    {
        bool sub_rule_result = _sub_rules[i].rule->test();
        if(_sub_rules[i].negate) sub_rule_result = !sub_rule_result;
        result = (_sub_rules[i].and_or ? (result && sub_rule_result) : (result || sub_rule_result));
    }
    return result;
}
