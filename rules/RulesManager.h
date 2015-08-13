//
// Created by Celito on 8/11/2015.
//

#ifndef BGCORE_RULESMANAGER_H
#define BGCORE_RULESMANAGER_H

#include <memory>
#include <map>
#include <vector>
#include <string>
#include "Rule.h"

using namespace std;

class RulesManager {
public:

    void add_static_rule(shared_ptr<Rule> rule);

    const vector< shared_ptr< Rule > > & get_rules(rule_usage_t usage, string piece_id);

private:
    // dictionary of the rules organized by usage and piece_id
    map<rule_usage_t, map<string, vector<shared_ptr<Rule>>>> _curr_rules_dictionary;

};


#endif //BGCORE_RULESMANAGER_H
