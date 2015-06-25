//
// Created by Celito on 2015-06-03.
//

#ifndef BGCORE_TURNSMAANGER_H
#define BGCORE_TURNSMAANGER_H


#include <stdint-gcc.h>
#include "Game.h"

class TurnsManager {
public:
    TurnsManager(Game *game);

    void StartTurn();
private:
    Game *_game;
    uint16_t _currentPlayer;
};


#endif //BGCORE_TURNSMAANGER_H
