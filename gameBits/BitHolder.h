//
// Created by Celito on 7/10/2015.
//

#ifndef BGCORE_BITHOLDER_H
#define BGCORE_BITHOLDER_H

#include <memory>
#include <list>
#include <vector>
#include "GameBit.h"

using namespace std;

class GameBit;

class BitHolder {
public:
    virtual ~BitHolder() {}
    virtual void receive(shared_ptr<GameBit> bit);
    bool is_empty() const;

protected:

    virtual void remove(shared_ptr<GameBit> bit);
    vector< weak_ptr<GameBit> > _bits;
};


#endif //BGCORE_BITHOLDER_H
