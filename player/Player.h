//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_PLAYER_H
#define BGCORE_PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "../gameBits/GameBit.h"

class PlayerInterface;
class PlayerController;
class PieceSet;
class Attribute;

using namespace std;

class Player : public GameBit {
public:
    Player(BgCore &game, uint8_t id);

    shared_ptr<GameBit> get_first_bit_by_name(string bit_name) const;

    shared_ptr<PlayerInterface> get_interface() const {
        return _interface;
    }

    shared_ptr<PlayerController> get_controller() { return _controller; }

    uint8_t get_player_id() { return  _id; }

    void set_controller(shared_ptr<PlayerController> controller);

private:
    uint8_t _id;

    shared_ptr<PlayerInterface> _interface;
    shared_ptr<PlayerController> _controller;
};


#endif //BGCORE_PLAYER_H
