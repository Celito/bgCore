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

using namespace std;

class Game {
public:
    Game();

    void Start();

private:
    //game config:
    uint32_t num_of_players;

    //game pointers:
    vector<shared_ptr<Player> > _players;

    //helper managers:
    shared_ptr<BitsManager> _bits;
};


#endif //BGCORE_GAMEMANAGER_H
