//
// Created by Celito on 2015-07-20.
//

#ifndef BGCORE_ENABLEMOVEMENTRULE_H
#define BGCORE_ENABLEMOVEMENTRULE_H


#include "Rule.h"
#include "../player/Player.h"

class PlayerAttrComparison : public Rule {
public:
    PlayerAttrComparison(Game &game): _game(game) {}

    bool test(GameBit const &bit);

    void set_tested_attr(string attr);

    void set_curr_player(shared_ptr<Player> player) { _player = player; }

private:
    shared_ptr<Player> _player;
    uint32_t _attr_id;

    Game &_game;
};


#endif //BGCORE_ENABLEMOVEMENTRULE_H
