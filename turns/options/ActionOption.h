//
// Created by Celito on 7/2/2015.
//

#ifndef BGCORE_ACTIONOPTION_H
#define BGCORE_ACTIONOPTION_H

#include <memory>
#include "Option.h"

using namespace std;

class Action;

class ActionOption : public  Option{
public:
    ActionOption(shared_ptr<Action> action) : _selected_action(action) {}

    string get_description();

    const shared_ptr<Action> &get_selected_action() const {
        return _selected_action;
    }

private:
    shared_ptr<Action> _selected_action;
};


#endif //BGCORE_ACTIONOPTION_H
