//
// Created by Celito on 7/8/2015.
//

#include <algorithm>
#include "ChoosePieceOnSet.h"
#include "../../gameBits/PieceSet.h"
#include "../../gameBits/BitReference.h"
#include "options/BitOption.h"

ChoosePieceOnSet::ChoosePieceOnSet(shared_ptr<BitReference> pieces_pool) {
    _bit_refs[e_piece_set] = pieces_pool;
}

string ChoosePieceOnSet::get_description() const {
    return "Choose a piece from this piece set";
}

void ChoosePieceOnSet::update_options(Action &action) {

    shared_ptr<PieceSet> pieces_pool =
            (shared_ptr<PieceSet>)dynamic_pointer_cast<PieceSet>(action.get_req_bit(e_piece_set));

    if(pieces_pool == nullptr) throw new exception();

    //TODO: Need to test rules that could filter this options;
    vector< shared_ptr<Piece> > pieces = pieces_pool->get_available_pieces();
    for(auto iter = pieces.begin(); iter != pieces.end(); iter++) {
        //TODO: Test if the concat action is available
        action.add_option(make_shared<BitOption>((*iter)));
    }
}

bool ChoosePieceOnSet::is_available(shared_ptr<Player> player) {
    shared_ptr<BitReference> &bit_ref = _bit_refs[e_piece_set];
    if(bit_ref == nullptr) throw new exception();
    shared_ptr<GameBit> bit_ptr = bit_ref->get_bit(player);
    if(bit_ptr == nullptr) throw new exception();
    shared_ptr<PieceSet> piece_set = (shared_ptr<PieceSet>)dynamic_pointer_cast<PieceSet>(bit_ptr);
    if(piece_set == nullptr) throw new exception();

    return piece_set != nullptr && !piece_set->is_empty();
}
