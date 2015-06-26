//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_PLAYER_H
#define BGCORE_PLAYER_H

#include <string>
#include <map>
#include <memory>

class GameBit;
class PlayerInterface;
class PieceSet;

using namespace std;

class Player {
public:
    Player(unsigned int id);

    void receive(shared_ptr<PieceSet> bit);

    const shared_ptr<PlayerInterface> &get_interface() const {
        return _interface;
    }

private:
    unsigned int _id;

    map<string, shared_ptr<GameBit> > _possessions;

    shared_ptr<PlayerInterface> _interface;
};


#endif //BGCORE_PLAYER_H
