//
// Created by Celito on 2015-06-25.
//

#ifndef BGCORE_PLAYERINTERFACE_H
#define BGCORE_PLAYERINTERFACE_H

#include <memory>
#include "Player.h"

using namespace std;

class PlayerInterface {
public:
    PlayerInterface(Player &player) : _player(player) {}

    uint32_t get_id() { return _player.get_player_id(); }
    
private:
    Player &_player;
};


#endif //BGCORE_PLAYERINT    