//
// Created by Celito on 8/11/2015.
//

#include "RulesManager.h"

void RulesManager::add_static_rule(shared_ptr<Rule> rule) {
    const vector<string> &bits_ids = rule->get_applicable_bits_ids();
    for (auto bits_id : bits_ids) {
        _curr_rules_dictionary[rule->get_usage()][bits_id].push_back(rule);
    }
}

const vector<shared_ptr<Rule> > &RulesManager::get_rules(rule_usage_t usage, string piece_id) {
    if(_curr_rules_dictionary.count(usage) == 0) throw new exception();
    if(_curr_rules_dictionary[usage].count(piece_id) == 0) throw new exception();
    return _curr_rules_dictionary[usage][piece_id];
}

void RulesManager::add_conditioned_rule(shared_ptr<Rule> rule, shared_ptr<TimedCondition> condition) {
    _conditioned_rules.push_back(pair<shared_ptr<Rule>, shared_ptr<TimedCondition>>(rule, condition));
    condition->on_satisfied([this, rule](){
        add_static_rule(rule);
    });
    condition->on_unsatisfied([this, rule](){
        const vector<string> &bits_ids = rule->get_applicable_bits_ids();
        for (auto bit_id : bits_ids) {
            vector<shared_ptr<Rule>> &rules_entry = _curr_rules_dictionary[rule->get_usage()][bit_id];
            rules_entry.erase(remove(rules_entry.begin(), rules_entry.end(), rule), rules_entry.end());
        }
    });
}
