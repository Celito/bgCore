//
// Created by Celito on 8/11/2015.
//

#include "RulesManager.h"

void RulesManager::add_static_rule(shared_ptr<Rule> rule) {
    const vector<uint32_t> &bits_ids = rule->get_applicable_bits_ids();
    _curr_rules_dictionary[rule->get_usage()].push_back(rule);
}

const vector<shared_ptr<Rule>> RulesManager::get_rules(rule_usage_t usage, uint32_t piece_id) const {
    vector<shared_ptr<Rule>> ret;
    if(_curr_rules_dictionary.count(usage) == 0) throw new exception();

    for (const shared_ptr<Rule> &rule : _curr_rules_dictionary.at(usage)) {
        const vector<uint32_t> &applicable_bits = rule->get_applicable_bits_ids();
        if(find(applicable_bits.cbegin(), applicable_bits.cend(), piece_id) != applicable_bits.cend()) {
            ret.push_back(rule);
        }
    }
    
    return ret;
}

void RulesManager::add_conditioned_rule(shared_ptr<Rule> rule, shared_ptr<TimedCondition> condition) {
    _conditioned_rules.push_back(pair<shared_ptr<Rule>, shared_ptr<TimedCondition>>(rule, condition));
    condition->on_satisfied([this, rule](){
        add_static_rule(rule);
    });
    condition->on_unsatisfied([this, rule](){
        const vector<uint32_t> &bits_ids = rule->get_applicable_bits_ids();
        vector<shared_ptr<Rule>> &rules_entry = _curr_rules_dictionary[rule->get_usage()];
        rules_entry.erase(remove(rules_entry.begin(), rules_entry.end(), rule), rules_entry.end());
    });
}
