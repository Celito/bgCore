//
// Created by Celito on 2015-05-29.
//

#include <algorithm>
#include "PieceSet.h"
#include "../Game.h"
#include "../BitsManager.h"

using namespace std;

PieceSet::PieceSet(Game &game, std::string refId) : GameBit(game, refId) {}

vector< shared_ptr<Piece> > PieceSet::get_available_pieces() const {
    vector< shared_ptr<Piece> > ret;
    // get only one piece by type
    for(auto iter = _bits.cbegin(); iter != _bits.cend(); iter++)
    {
        if(iter->expired()) break;
        ret.push_back((shared_ptr<Piece>)dynamic_pointer_cast<Piece>(iter->lock()));
        // Skip the pieces with the same bit_id
        while((iter+1) != _bits.cend() && (*iter).lock()->get_bit_id() == (*(iter+1)).lock()->get_bit_id()) iter++;
    }
    return ret;
}

void PieceSet::receive(shared_ptr<GameBit> bit) {
    if(!dynamic_pointer_cast<Piece>(bit)) throw;
    BitHolder::receive(bit);
}
