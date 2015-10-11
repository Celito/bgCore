//
// Created by Celito on 7/3/2015.
//

#ifndef BGCORE_OPTION_H
#define BGCORE_OPTION_H

#include <memory>
#include <string>

using namespace std;

class Action;

class Option
{
public:
    virtual string get_description() = 0;

    void set_pre_processed_next_action(const shared_ptr<Action> &next_action) { _pre_processed_next_action = next_action; }

    const shared_ptr<Action> & get_pre_processed_next_action() { return _pre_processed_next_action; }

private:
    shared_ptr<Action> _pre_processed_next_action;
};


#endif //BGCORE_OPTION_H
