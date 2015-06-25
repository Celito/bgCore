//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_PLAYER_H
#define BGCORE_PLAYER_H

#include <string>
#include <map>
#include "gameBits/GameBit.h"

using namespace std;

class Player {
public:
    Player(unsigned int id);

    map<string, GameBit*> Posetions;
private:
    unsigned int _id;
};


#endif //BGCORE_PLAYER_H
