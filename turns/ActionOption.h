//
// Created by Celito on 7/2/2015.
//

#ifndef BGCORE_ACTIONOPTION_H
#define BGCORE_ACTIONOPTION_H

#include <memory>
#include "Action.h"

using namespace std;

class ActionOption {
public:
    ActionOption(shared_ptr<Action> action) : _selected_action(action) {}

    string get_description();

private:
    shared_ptr<Action> _selected_action;
};


#endif //BGCORE_ACTIONOPTION_H
