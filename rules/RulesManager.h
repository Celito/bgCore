//
// Created by Celito on 8/11/2015.
//

#ifndef BGCORE_RULESMANAGER_H
#define BGCORE_RULESMANAGER_H

#include <memory>
#include <map>
#include <vector>
#include <string>

enum rule_usage_t {
    e_movement_rule,
    e_placement_rule,
    e_movement_enable_rule
};

class Rule;

using namespace std;

class RulesManager {
public:

    void add_rule(rule_usage_t usage, string piece_id, shared_ptr<Rule> rule);

    const vector< shared_ptr< Rule > > & get_rules(rule_usage_t usage, string piece_id);

private:
    // dictionary of the rules organized by usage and piece_id
    map< rule_usage_t, map < string, vector < shared_ptr < Rule > > > > _rules_dictionary;
};


#endif //BGCORE_RULESMANAGER_H
