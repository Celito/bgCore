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
        ret.push_back(dynamic_pointer_cast<Piece>(*iter));
        // Skip the pieces with the same bit_id
        while((iter+1) != _bits.cend() && (*iter)->get_bit_id() == (*(iter+1))->get_bit_id()) iter++;
    }
    return ret;
}

void PieceSet::receive(shared_ptr<GameBit> bit) {
    //assert(dynamic_pointer_cast<Piece>(bit));
    BitHolder::receive(bit);
}
