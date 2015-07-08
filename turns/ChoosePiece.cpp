//
// Created by Celito on 7/8/2015.
//

#include "ChoosePiece.h"
#include "../gameBits/PieceSet.h"
#include "../gameBits/BitReference.h"

void ChoosePiece::init(shared_ptr<Player> player) {
    Action::init(player);
    _pieces_pool = dynamic_pointer_cast<PieceSet>(_pieces_pool_ref.get_from_player(player));
    vector<shared_ptr<Piece>> pieces = _pieces_pool->get_pieces();
    for(auto iter = pieces.cbegin(); iter == pieces.cend(); iter++) {
        //TODO: create and add the proper options for each piece in the piece_pool
    }
}

bool ChoosePiece::is_available() const {
    return _pieces_pool && !_pieces_pool->is_empty();
}

string ChoosePiece::get_description() const {
    return "Choose a piece from this piece set";
}

ChoosePiece::ChoosePiece(BitReference pieces_pool) : _pieces_pool_ref(pieces_pool) {}

void ChoosePiece::choose(shared_ptr<Option> option) {

}
