//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_ACTION_H
#define BGCORE_ACTION_H

#include "../player/Player.h"
#include "../gameBits/BitReference.h"

using namespace std;

class ActionOption;

class Action {
public:

    virtual ~Action() {}

    virtual void apply_to(shared_ptr<Player> player);

    //Interface:

    virtual bool is_available() const = 0;

    virtual const vector< shared_ptr <ActionOption> >& get_options() const;

    virtual string get_description() const = 0;

protected:
    vector< shared_ptr <ActionOption> > _options;
    vector<BitReference> _references;
    shared_ptr<Player> _curr_player;
};


#endif //BGCORE_ACTION_H
