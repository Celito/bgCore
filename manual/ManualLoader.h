//
// Created by Celito on 2018-09-17.
//

#ifndef BGCORE_MANUALLOADER_H
#define BGCORE_MANUALLOADER_H

#include <c++/string>
#include <c++/vector>
#include "ManualProperty.h"

using namespace std;

class BgCore;

class ManualLoader
{
public:
    ManualLoader(BgCore & game, string & manualFile);
private:
    BgCore &_game;

    vector<ManualProperty *> _rootProperties;
};


#endif //BGCORE_MANUALLOADER_H
