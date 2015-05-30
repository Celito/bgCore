//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_GAMEMANAGER_H
#define BGCORE_GAMEMANAGER_H

#include <vector>

class Player;
class BitsManager;
class ConfigManager;

class GameManager {
public:
    GameManager();

    std::vector<Player* > *Players;
    BitsManager *Bits;
    ConfigManager *Config;
};


#endif //BGCORE_GAMEMANAGER_H
