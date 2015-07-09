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
    // Make sure the pieces are always arranged by their unique id;
    _pieces.insert(find_if(_pieces.begin(),_pieces.end(),
                           [&piece](shared_ptr<Piece> p){
                               return p->get_unique_id() > piece->get_unique_id();
                           }), piece);
}

bool PieceSet::is_empty() const {
    return _pieces.size() == 0;
}

vector< shared_ptr<Piece> > PieceSet::get_available_pieces() const {
    vector< shared_ptr<Piece> > ret;
    // get only one piece by type
    for(auto iter = _pieces.cbegin(); iter != _pieces.cend(); iter++)
    {
        ret.push_back(*iter);
        // Skip the pieces with the same bit_id
        while((iter+1) != _pieces.cend() && (*iter)->get_bit_id() == (*(iter+1))->get_bit_id()) iter++;
    }
    return ret;
}