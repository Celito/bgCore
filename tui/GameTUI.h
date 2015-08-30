//
// Created by Celito on 2015-06-25.
//

#ifndef BGCORE_GAMETUI_H
#define BGCORE_GAMETUI_H


#include <queue>
#include "../BgCore.h"
#include "../GameController.h"

class PlayerTUI;
class PlayerController;

using namespace std;

class GameTUI : public GameController {

public:
    GameTUI(BgCore &game);

    virtual shared_ptr<PlayerController> get_player_controller(uint32_t player_id) override;

    void run();

    int32_t get_next_pre_loaded_option();

private:
    BgCore &_game;

    vector< shared_ptr<PlayerTUI> > _player_TUIS;

    queue< int > pre_loaded_opt;
};


#endif //BGCORE_GAMETUI_H
