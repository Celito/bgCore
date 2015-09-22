//
// Created by Celito on 2015-06-25.
//

#include "GameTUI.h"
#include "PlayerTUI.h"

GameTUI::GameTUI(BgCore &game) : _game(game) {
    auto num = _game.get_num_of_players();
    for (uint32_t i = 0; i < num; ++i) {
        _player_TUIS.push_back(make_shared<PlayerTUI>(*this));
    }
    // Ant can't jump test case
//    const vector<int32_t> t = {1, 0, 1, 4, 0, 1, 7, 0, 1, 6, 0, 1, 3, 0, 3, 9, 0, 3, 7, 1, 3};

    // Bug on placement
//    const vector<int32_t> t = {0,0,0,3,0,2,1,0,2,2,1,1,0,1,1,0,0,0}

    // Bug on ant movement
//    const vector<int32_t> t = {4,0,4,5,0,4,2,1};;

//    const vector<int32_t> t = {1, 0, 1, 4, 1, 0, 0, 0, 1, 6, 1, 0};
//    for_each(t.cbegin(),t.cend(), [this](int32_t n) { pre_loaded_opt.push(n); });
}

void GameTUI::run() {
    _game.start(*this);
}

shared_ptr<PlayerController> GameTUI::get_player_controller(uint32_t player_id) {
    return _player_TUIS[player_id];
}

int32_t GameTUI::get_next_pre_loaded_option() {
    if (pre_loaded_opt.size() > 0) {
        int ret = pre_loaded_opt.front();
        pre_loaded_opt.pop();
        return ret;
    }
    else {
        return -1;
    }
}
