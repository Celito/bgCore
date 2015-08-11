//
// Created by Celito on 8/11/2015.
//

#include "RulesManager.h"

void RulesManager::add_rule(rule_usage_t usage, string piece_id, shared_ptr<Rule> rule) {
    _rules_dictionary[usage][piece_id].push_back(rule);
}

const vector<shared_ptr<Rule> > &RulesManager::get_rules(rule_usage_t usage, string piece_id) {
    return _rules_dictionary[usage][piece_id];
}
