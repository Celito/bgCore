//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_PLAYERCONTROLLER_H
#define BGCORE_PLAYERCONTROLLER_H

#include <memory>

class Action;

using  namespace std;

class PlayerController {
public:
    virtual void resolve_action(weak_ptr<Action> action) = 0;
};


#endif //BGCORE_PLAYERCONTROLLER_H
