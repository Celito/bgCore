//
// Created by Celito on 2015-05-29.
//

#include <algorithm>
#include "PieceSet.h"
#include "../Game.h"
#include "../BitsManager.h"

using namespace std;

PieceSet::PieceSet(Game &game, std::string refId) : GameBit(game, refId) {}

void PieceSet::add_piece(shared_ptr<Piece> piece) {
    _pieces.insert(find_if(_pieces.begin(),_pieces.end(),
                           [&piece](shared_ptr<Piece> p){
                               return p->get_unique_id() > piece->get_unique_id();
                           }), piece);
}

bool PieceSet::is_empty() const {
    return _pieces.size() == 0;
}

vector<shared_ptr<Piece> > const &PieceSet::get_pieces() const {
    return _pieces;
}

bool game_bit_compare_bit_id(shared_ptr<Piece> p1, shared_ptr<Piece> p2){
    return !p1 || !p2 || p1->get_bit_id() != p2->get_bit_id();
}