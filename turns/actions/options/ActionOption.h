//
// Created by Celito on 7/2/2015.
//

#ifndef BGCORE_ACTIONOPTION_H
#define BGCORE_ACTIONOPTION_H

#include <memory>
#include <string>
#include "Option.h"

using namespace std;

class ActionDef;

class ActionOption : public  Option{
public:
    ActionOption(shared_ptr<ActionDef> action) : _selected_action(action) {}

    string get_description();

    const shared_ptr<ActionDef> &get_selected_action() const {
        return _selected_action;
    }

private:
    shared_ptr<ActionDef> _selected_action;
};


#endif //BGCORE_ACTIONOPTION_H
