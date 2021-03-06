//
// Created by Celito on 2015-06-03.
//

#ifndef BGCORE_TURNSMAANGER_H
#define BGCORE_TURNSMAANGER_H


#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/signals2.hpp>

class BgCore;
class TurnDef;
class Turn;
class Action;
class State;

using  namespace std;

class TurnsManager {
public:
    TurnsManager(BgCore &game);

    void register_player_turn_def(uint8_t player_id, shared_ptr<TurnDef> turn);

    void next_turn();

    void kill();

    const shared_ptr<State> &get_curr_state();

    uint32_t round();

    boost::signals2::connection on_round_changed(boost::signals2::slot<void()> slot);

    boost::signals2::connection on_turn_changed(boost::signals2::slot<void()> slot);

private:
    BgCore &_game;
    uint8_t _curr_player_id;
    uint32_t _curr_round;

    map<uint8_t, vector<shared_ptr<TurnDef>>> _player_turn_defs;
    vector<shared_ptr<Turn>> _match_turns;

    shared_ptr<Turn> _curr_turn;
    shared_ptr<Action> _curr_action;
    shared_ptr<State> _curr_state;

    boost::signals2::signal<void()> _turn_changed;
    boost::signals2::signal<void()> _round_changed;
    bool _killed;
};


#endif //BGCORE_TURNSMAANGER_H
