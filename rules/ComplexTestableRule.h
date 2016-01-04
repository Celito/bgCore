//
// Created by Celito on 10/16/2015.
//

#ifndef BGCORE_COMPLEXTESTABLERULE_H
#define BGCORE_COMPLEXTESTABLERULE_H


#include "TestableRule.h"

struct sub_rule_t {
    shared_ptr<TestableRule> rule;
    bool negate;
    bool and_or;
};

class ComplexTestableRule : public TestableRule {
public:
    ComplexTestableRule(BgCore &game) : TestableRule(game) { }

    void concat_rule(const shared_ptr<TestableRule> &sub_rule);

    void concat_rule(const shared_ptr<TestableRule> &sub_rule, bool negate, bool and_or);


    virtual bool test() override;

private:
    vector<sub_rule_t> _sub_rules;
};


#endif //BGCORE_COMPLEXTESTABLERULE_H
