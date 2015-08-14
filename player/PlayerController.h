//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_PLAYERCONTROLLER_H
#define BGCORE_PLAYERCONTROLLER_H

#include <memory>

class Action;
class PlayerInterface;

using  namespace std;

class PlayerController {
public:

    virtual void resolve_action(shared_ptr<Action> action) = 0;

    void set_interface(const shared_ptr<PlayerInterface> &interface) {
        _interface = interface;
    }

    const weak_ptr<PlayerInterface> &get_interface() const { return _interface; }

private:

    weak_ptr<PlayerInterface> _interface;

};


#endif //BGCORE_PLAYERCONTROLLER_H
