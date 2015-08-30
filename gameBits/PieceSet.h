//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_PIECESET_H
#define BGCORE_PIECESET_H

#include <iostream>
#include <vector>
#include <list>
#include "GameBit.h"
#include "Piece.h"

using namespace std;

class PieceSet : public GameBit {

public:
    PieceSet(BgCore &game, string refId);

    vector< shared_ptr<Piece> > get_available_pieces() const;

    virtual void receive(shared_ptr<GameBit> bit) override;
};


#endif //BGCORE_PIECESET_H
