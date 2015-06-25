//
// Created by Celito on 2015-06-25.
//

#ifndef BGCORE_GAMETUI_H
#define BGCORE_GAMETUI_H


#include "../Game.h"

class GameTUI {

public:
    GameTUI(Game &game) : _game(game) { }

    void Run();

private:
    Game &_game;
};


#endif //BGCORE_GAMETUI_H
