//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_PLAYER_H
#define BGCORE_PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "../gameBits/GameBit.h"

class GameBit;
class PlayerInterface;
class PlayerController;
class PieceSet;

using namespace std;

class Player {
public:
    Player(Game &game, unsigned int id);

    void receive(shared_ptr<PieceSet> bit);

    shared_ptr<GameBit> get_bit(string bit_id) const;

    shared_ptr<PlayerInterface> get_interface() const {
        return _interface;
    }

    shared_ptr<PlayerController> get_controller() {
        return _controller;
    }

    Game &get_curr_game() {
        return _game;
    }

    void set_controller(shared_ptr<PlayerController> _controller) {
        Player::_controller = _controller;
    }

private:
    Game &_game;
    unsigned int _id;

    vector< shared_ptr<GameBit> > _possessions;

    shared_ptr<PlayerInterface> _interface;
    shared_ptr<PlayerController> _controller;
};


#endif //BGCORE_PLAYER_H
