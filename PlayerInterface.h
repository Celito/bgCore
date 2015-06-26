//
// Created by Celito on 2015-06-25.
//

#ifndef BGCORE_PLAYERINTERFACE_H
#define BGCORE_PLAYERINTERFACE_H

#include <memory>

using namespace std;

class Player;

class PlayerInterface {
public:
    PlayerInterface(shared_ptr<Player> player) : _player(player) {}
    
private:
    shared_ptr<Player> _player;
};


#endif //BGCORE_PLAYERINT    