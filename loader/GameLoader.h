//
// Created by CelitFel on 2019-02-28.
//

#ifndef BGCORE_GAMELOADER_H
#define BGCORE_GAMELOADER_H

#include <string>
#include <vector>
#include "../BgCore.h"
#include "ReservedWord.h"

using namespace std;
using namespace gameLoader;

class GameLoader {
public:
    GameLoader(BgCore &game);

    void LoadRules(const string &filename);

private:
    vector< shared_ptr<ReservedWord> > _wordsDictionary;
};


#endif //BGCORE_GAMELOADER_H
