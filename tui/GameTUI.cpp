//
// Created by Celito on 2015-06-25.
//

#include "GameTUI.h"
#include "PlayerTUI.h"

GameTUI::GameTUI(Game &game) : _game(game) {
    auto num = _game.get_num_of_players();
    for (uint32_t i = 0; i < num; ++i) {
        _player_TUIS.push_back(make_shared<PlayerTUI>());
    }
}

void GameTUI::run() {
    _game.start(*this);
}

shared_ptr<PlayerController> GameTUI::get_player_controller(uint32_t player_id) {
    return _player_TUIS[player_id];
}
