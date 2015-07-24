//
// Created by Celito on 7/8/2015.
//

#include <algorithm>
#include "ChoosePieceOnSet.h"
#include "../gameBits/PieceSet.h"
#include "options/BitOption.h"

ChoosePieceOnSet::ChoosePieceOnSet(shared_ptr<BitReference> pieces_pool) {
    _bit_refs[e_piece_set] = pieces_pool;
}

string ChoosePieceOnSet::get_description() const {
    return "Choose a piece from this piece set";
}

void ChoosePieceOnSet::update_options() {
    _options.clear();
    //assert(_required_bits.count(e_piece_set) != 0 && !_required_bits[e_piece_set].expired());

    auto pieces_pool = dynamic_pointer_cast<PieceSet>(_required_bits[e_piece_set].lock());

    //assert(pieces_pool != nullptr);

    //TODO: Need to test rules that could filter this options;
    vector< shared_ptr<Piece> > pieces = pieces_pool->get_available_pieces();
    for(auto iter = pieces.begin(); iter != pieces.end(); iter++) {
        //TODO: Test if the concat action is available
        _options.push_back(make_shared<BitOption>((*iter)));
    }
}
