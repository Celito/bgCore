//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_GAMEMANAGER_H
#define BGCORE_GAMEMANAGER_H

#include <vector>
#include <memory>
#include <map>

class Player;
class BitsManager;
class ConfigManager;
class GameBit;
class TurnsManager;
class PlayerController;
class GameController;

using namespace std;

class Game {
public:
    Game();

    //interface:
    void start(GameController &game_controller);

    //internal:
    shared_ptr<Player> get_player(uint32_t id);

    uint32_t get_num_of_players() const {
        return _num_of_players;
    }

    shared_ptr<GameBit> get_table_bit(string bit_id) const;

private:
//game config:
    uint32_t _num_of_players;

    //game pointers:
    vector< shared_ptr<Player> > _players;
    vector< shared_ptr<GameBit> > _table;

    //helper managers:
    shared_ptr<BitsManager> _bits;
    shared_ptr<TurnsManager> _turns;
};


#endif //BGCORE_GAMEMANAGER_H
