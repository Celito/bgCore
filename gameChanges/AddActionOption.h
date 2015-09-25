//
// Created by Celito on 9/25/2015.
//

#ifndef BGCORE_ADDACTIONOPTION_H
#define BGCORE_ADDACTIONOPTION_H


#include "GameChange.h"

class AddActionOption : public GameChange {
public:
    AddActionOption(BgCore &core) : GameChange(core) {}

    virtual void apply();
};


#endif //BGCORE_ADDACTIONOPTION_H
