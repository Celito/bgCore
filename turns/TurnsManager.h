//
// Created by Celito on 2015-06-03.
//

#ifndef BGCORE_TURNSMAANGER_H
#define BGCORE_TURNSMAANGER_H


#include <vector>
#include <memory>
#include <stdint-gcc.h>

class Game;
class Turn;

using  namespace std;

class TurnsManager {
public:
    TurnsManager(Game &game);

    void register_turn(shared_ptr<Turn> turn);

    void start_turn();
private:
    Game &_game;
    uint32_t _current_player_id;

    vector<shared_ptr<Turn> > _possible_turns;
};


#endif //BGCORE_TURNSMAANGER_H
