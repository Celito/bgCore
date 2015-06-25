//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_GAMEMANAGER_H
#define BGCORE_GAMEMANAGER_H

#include <vector>
#include <memory>

class Player;
class BitsManager;
class ConfigManager;

class Game {
public:
    Game();

    void Start();

private:
    std::vector<std::shared_ptr<Player> > _players;
    BitsManager *Bits;
    ConfigManager *Config;
};


#endif //BGCORE_GAMEMANAGER_H
