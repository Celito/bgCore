//
// Created by Celito on 2015-06-25.
//

#ifndef BGCORE_GAMETUI_H
#define BGCORE_GAMETUI_H


#include "../Game.h"
#include "../GameController.h"

class PlayerTUI;
class PlayerController;

using namespace std;

class GameTUI : public GameController {

public:
    GameTUI(Game &game);

    virtual shared_ptr<PlayerController> get_player_controller(uint32_t player_id) override;

    void run();

private:
    Game &_game;

    vector< shared_ptr<PlayerTUI> > _player_TUIS;
};


#endif //BGCORE_GAMETUI_H
