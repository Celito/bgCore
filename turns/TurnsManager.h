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

using  namespace std;

class TurnsManager {
public:
    TurnsManager(Game &game);

    void register_turn(shared_ptr<TurnDef> turn);

    void next_turn();
private:
    Game &_game;
    uint32_t _current_player_id;

    vector<shared_ptr<TurnDef> > _possible_turns;
};


#endif //BGCORE_TURNSMAANGER_H
