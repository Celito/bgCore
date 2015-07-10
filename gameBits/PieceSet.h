//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_PIECESET_H
#define BGCORE_PIECESET_H

#include <c++/iostream>
#include <vector>
#include <list>
#include "GameBit.h"
#include "BitHolder.h"
#include "Piece.h"

using namespace std;

class PieceSet : public GameBit, public BitHolder {

public:
    PieceSet(Game &game, string refId);

    vector< shared_ptr<Piece> > get_available_pieces() const;

    virtual void receive(shared_ptr<GameBit> bit) override;
};


#endif //BGCORE_PIECESET_H
