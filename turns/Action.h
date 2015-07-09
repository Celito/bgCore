//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_ACTION_H
#define BGCORE_ACTION_H

#include "../player/Player.h"
#include "../gameBits/BitReference.h"
#include <boost/signals2.hpp>

using namespace std;

class Option;

class Action {
public:

    virtual ~Action() {}

    virtual void init(shared_ptr<Player> player);

    void set_next_action(shared_ptr<Action> next_action) {
        _next_action = next_action;
    }

    weak_ptr<Action> get_next_action() const {
        return _next_action;
    }

    virtual bool self_resolve()  { return false; }

    virtual bool is_available() const = 0;

    //Interface:

    virtual const vector< shared_ptr <Option> >& get_options() const;

    virtual string get_description() const = 0;

    virtual void choose(shared_ptr<Option> option);

    boost::signals2::connection on_option_taken(boost::signals2::slot<void(shared_ptr<Option>)> slot);

protected:
    vector< shared_ptr <Option> > _options;
    vector<BitReference> _references;
    shared_ptr<Player> _curr_player;
    weak_ptr<Action> _next_action;

    boost::signals2::signal<void(shared_ptr<Option>)> _option_taken;
};


#endif //BGCORE_ACTION_H
