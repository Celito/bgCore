//
// Created by Celito on 8/10/2015.
//

#ifndef BGCORE_TESTABLERULE_H
#define BGCORE_TESTABLERULE_H

#include <memory>
#include <map>
#include "Rule.h"
#include "../gameBits/GameBit.h"

class Player;
class Game;

using namespace std;

class TestableRule : public Rule {
public:
    TestableRule(Game &game) : _game(game) {}

    virtual bool test() = 0;

    void set_curr_player(shared_ptr<Player> player) { _player = player; }

    void add_req_bit(bit_types_e bit_type, shared_ptr<GameBit> req_bit);

protected:
    weak_ptr<Player> _player;

    map<bit_types_e, weak_ptr<GameBit> > _required_bits;

    Game &_game;
};


#endif //BGCORE_TESTABLERULE_H
