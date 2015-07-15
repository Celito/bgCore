//
// Created by Celito on 7/8/2015.
//

#include <algorithm>
#include "ChoosePieceOnSet.h"
#include "../gameBits/PieceSet.h"
#include "../gameBits/BitReference.h"
#include "options/BitOption.h"

void ChoosePiece::init(shared_ptr<Player> player) {
    Action::init(player);
    _options.clear();
    _pieces_pool = dynamic_pointer_cast<PieceSet>(_pieces_pool_ref.get_from_player(player));
    vector<shared_ptr<Piece>> pieces = _pieces_pool->get_available_pieces();

    for(auto iter = pieces.begin(); iter != pieces.end(); iter++) {
        _options.push_back(make_shared<BitOption>((*iter)));
    }
}

bool ChoosePiece::is_available() const {
    return _pieces_pool && !_pieces_pool->is_empty();
}

string ChoosePiece::get_description() const {
    return "Choose a piece from this piece set";
}

ChoosePiece::ChoosePiece(BitReference pieces_pool) : _pieces_pool_ref(pieces_pool) {}
