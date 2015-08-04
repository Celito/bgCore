//
// Created by Celito on 2015-08-03.
//

#ifndef BGCORE_ACTION_H
#define BGCORE_ACTION_H

#include <memory>

class Turn;

using namespace std;

class Action {


private:
public:
    Action(const weak_ptr<Turn> &turn) : _turn(turn) { }

private:
    weak_ptr<Turn> _turn;
};


#endif //BGCORE_ACTION_H
