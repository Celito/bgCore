//
// Created by Celito on 2015-06-03.
//

#ifndef BGCORE_TURNSMAANGER_H
#define BGCORE_TURNSMAANGER_H


#include <vector>
#include <memory>
#include <stdint-gcc.h>

class Game;
class TurnDef;
class Turn;

using  namespace std;

class TurnsManager {
public:
    TurnsManager(Game &game);

    void register_turn_def(shared_ptr<TurnDef> turn);

    void next_turn();
private:
    Game &_game;
    uint32_t _current_player_id;

    vector< shared_ptr<TurnDef> > _turn_definitions;
    vector< shared_ptr<Turn> > _match_turns;
};


#endif //BGCORE_TURNSMAANGER_H
