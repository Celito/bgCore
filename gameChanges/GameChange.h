//
// Created by Celito on 9/25/2015.
//

#ifndef BGCORE_GAMECHANGE_H
#define BGCORE_GAMECHANGE_H


#include "../BgCore.h"

class GameChange {
public:
    GameChange(BgCore &core) : _core(core) {}

    virtual void apply();

protected:
    BgCore &_core;
};


#endif //BGCORE_GAMECHANGE_H
