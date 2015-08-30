//
// Created by Celito on 2015-06-03.
//

#ifndef BGCORE_TURNSMAANGER_H
#define BGCORE_TURNSMAANGER_H


#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/signals2.hpp>

class Game;
class TurnDef;
class Turn;
class Action;
class State;

using  namespace std;

class TurnsManager {
public:
    TurnsManager(Game &game);

    void register_turn_def(shared_ptr<TurnDef> turn);

    void next_turn();

    const shared_ptr<State> &get_curr_state();

    uint32_t round();

    boost::signals2::connection on_round_changed(boost::signals2::slot<void()> slot);

    boost::signals2::connection on_turn_changed(boost::signals2::slot<void()> slot);

private:
    Game &_game;
    uint32_t _curr_player_id;
    uint32_t _curr_round;

    vector< shared_ptr<TurnDef> > _turn_definitions;
    vector< shared_ptr<Turn> > _match_turns;

    shared_ptr<Turn> _curr_turn;
    shared_ptr<Action> _curr_action;
    shared_ptr<State> _curr_state;

    boost::signals2::signal<void()> _turn_changed;
    boost::signals2::signal<void()> _round_changed;
};


#endif //BGCORE_TURNSMAANGER_H
