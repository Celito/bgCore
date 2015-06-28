//
// Created by Celito on 2015-05-29.
//

#include "PieceSet.h"
#include "../Game.h"
#include "../BitsManager.h"

using namespace std;

PieceSet::PieceSet(Game &game, std::string refId) : GameBit(game, refId) {}

void PieceSet::add_piece(shared_ptr<Piece> piece) {
    _pieces.push_back(piece);
}

bool PieceSet::is_empty() {
    return _pieces.size() == 0;
}
