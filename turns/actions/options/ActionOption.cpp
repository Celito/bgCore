//
// Created by Celito on 7/2/2015.
//

#include "ActionOption.h"
#include "../ActionDef.h"

string ActionOption::get_description() {
    return _selected_action->get_description();
}
