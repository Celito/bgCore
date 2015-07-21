//
// Created by Celito on 2015-07-20.
//

#include "ChoosePieceOnBoard.h"
#include "../gameBits/boards/Board.h"
#include "../gameBits/Piece.h"
#include "options/BitOption.h"

ChoosePieceOnBoard::ChoosePieceOnBoard(shared_ptr<BitReference> target_board) {
    _bit_refs[e_board] = target_board;
}

string ChoosePieceOnBoard::get_description() const {
    return "Choose a piece from the board";
}

void ChoosePieceOnBoard::update_options() {
    _options.clear();
    shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(_required_bits[e_board]);

    if(board == nullptr) return;

    vector< shared_ptr<Piece> > pieces = board.get()->get_pieces();
    for (auto piece : pieces) {
        _options.push_back(make_shared<BitOption>(piece));
    }
}
