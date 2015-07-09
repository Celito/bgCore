//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_PIECESET_H
#define BGCORE_PIECESET_H

#include <c++/iostream>
#include <vector>
#include <list>
#include "GameBit.h"
#include "Piece.h"

using namespace std;

class PieceSet : public GameBit {

public:
    PieceSet(Game &game, string refId);

    void add_piece(shared_ptr<Piece> piece);

    vector<shared_ptr<Piece> > const &get_pieces() const;

    bool is_empty() const;

private:
    vector<shared_ptr<Piece> > _pieces;
};

bool game_bit_compare_bit_id(shared_ptr<Piece> p1, shared_ptr<Piece> p2);


#endif //BGCORE_PIECESET_H
