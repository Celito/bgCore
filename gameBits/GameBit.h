//
// Created by Celito on 2015-05-29.
//


#ifndef BGCORE_GAMEBIT_H
#define BGCORE_GAMEBIT_H

#include <memory>

using namespace std;

class Game;

class GameBit {
public:
    GameBit(Game &game, string bit_id);

    virtual ~GameBit() {};

    string get_unique_id() const;

    void set_ref_id(const uint32_t _ref_id) {
        GameBit::_ref_id = _ref_id;
    }

    const string &get_bit_id() const {
        return _bit_id;
    }

protected:
    Game &_game;
    uint32_t _ref_id;
    string _bit_id;
};


#endif //BGCORE_GAMEBIT_H
