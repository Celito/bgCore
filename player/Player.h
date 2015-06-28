//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_PLAYER_H
#define BGCORE_PLAYER_H

#include <string>
#include <map>
#include <memory>

class GameBit;
class PlayerInterface;
class PlayerController;
class PieceSet;

using namespace std;

class Player {
public:
    Player(unsigned int id);

    void receive(shared_ptr<PieceSet> bit);

    shared_ptr<PlayerInterface> get_interface() const {
        return _interface;
    }

    shared_ptr<PlayerController> get_controller() {
        return _controller;
    }

    void set_controller(shared_ptr<PlayerController> _controller) {
        Player::_controller = _controller;
    }

private:
    unsigned int _id;

    map<string, shared_ptr<GameBit> > _possessions;

    shared_ptr<PlayerInterface> _interface;
    shared_ptr<PlayerController> _controller;
};


#endif //BGCORE_PLAYER_H
