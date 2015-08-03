//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_ACTION_H
#define BGCORE_ACTION_H

#include <boost/signals2.hpp>

using namespace std;

class Option;
class Player;
class GameBit;
class BitReference;

enum required_bit_t{
    e_tile,
    e_piece,
    e_piece_set,
    e_board
};

class Action {
public:

    virtual ~Action() {}

    virtual void init(shared_ptr<Player> player);

    void set_next_action(shared_ptr<Action> next_action) { _next_action = next_action; }

    weak_ptr<Action> get_next_action() const { return _next_action; }

    void set_required_bit(required_bit_t bit_type, shared_ptr<GameBit> bit);

    /*
     * Pass the generated bits of this action to the required bits of the concated action;
     */
    virtual void concat_action(shared_ptr<Action> other_action);

    virtual bool self_resolve()  { return false; }

    virtual bool is_available() const ;

    virtual void update_options() = 0;

    //Interface:

    virtual string get_description() const = 0;

    virtual const vector< shared_ptr <Option> >& get_options() const;

    virtual void choose(shared_ptr<Option> option);

    boost::signals2::connection on_option_taken(boost::signals2::slot<void(shared_ptr<Option>)> slot);

protected:
    vector< shared_ptr <Option> > _options;
    map< required_bit_t, weak_ptr<GameBit> > _selected_bits;
    map< required_bit_t, weak_ptr<GameBit> > _required_bits;
    map< required_bit_t, shared_ptr<BitReference> > _bit_refs;
    shared_ptr<Player> _curr_player;
    weak_ptr<Action> _next_action;

    boost::signals2::signal<void(shared_ptr<Option>)> _option_taken;
};


#endif //BGCORE_ACTION_H
