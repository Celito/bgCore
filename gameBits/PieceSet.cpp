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
    const vector<weak_ptr<GameBit>> &children = get_children();
    // get only one piece by type
    for(auto iter = children.cbegin(); iter != children.cend(); iter++)
    {
        if(iter->expired()) break;
        ret.push_back((shared_ptr<Piece>)dynamic_pointer_cast<Piece>(iter->lock()));
        // Skip the pieces with the same bit_id
        while((iter+1) != children.cend() && (*iter).lock()->get_bit_id() == (*(iter+1)).lock()->get_bit_id()) iter++;
    }
    return ret;
}

void PieceSet::receive(shared_ptr<GameBit> bit) {
    if(!dynamic_pointer_cast<Piece>(bit)) throw new exception();
    GameBit::receive(bit);
}
