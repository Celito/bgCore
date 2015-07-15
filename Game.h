//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_GAMEMANAGER_H
#define BGCORE_GAMEMANAGER_H

#include <vector>
#include <memory>
#include <map>
#include "gameBits/BitHolder.h"

class Player;
class BitsManager;
class ConfigManager;
class GameBit;
class TurnsManager;
class PlayerController;
class GameController;

using namespace std;

class Game : public virtual BitHolder{
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

    void register_new_bit(shared_ptr<GameBit> bit);

private:
//game config:
    uint32_t _num_of_players;

    //game pointers:
    vector< shared_ptr<Player> > _players;

    //helper managers:
    shared_ptr<BitsManager> _bits_manager;
    shared_ptr<TurnsManager> _turns;
    bool _is_over;
};


#endif //BGCORE_GAMEMANAGER_H
