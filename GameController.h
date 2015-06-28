//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_GAMECONTROLLER_H
#define BGCORE_GAMECONTROLLER_H

#include <memory>

class PlayerController;

using namespace std;

class GameController {
public:
    virtual shared_ptr<PlayerController> get_player_controller(uint32_t player_id) = 0;
};


#endif //BGCORE_GAMECONTROLLER_H
