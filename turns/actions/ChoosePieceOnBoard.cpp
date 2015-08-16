//
// Created by Celito on 2015-07-20.
//

#include "ChoosePieceOnBoard.h"
#include "../../gameBits/boards/Board.h"
#include "../../gameBits/Piece.h"
#include "../../gameBits/BitReference.h"
#include "options/BitOption.h"

ChoosePieceOnBoard::ChoosePieceOnBoard(Game &game, shared_ptr<BitReference> target_board) : ActionDef(game) {
    _bit_refs[e_board] = target_board;
}

string ChoosePieceOnBoard::get_description() const {
    return "Choose a piece from the board";
}

void ChoosePieceOnBoard::update_options(Action &action) {

    shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(action.get_req_bit(e_board));

    vector< shared_ptr<Piece> > pieces = board.get()->get_pieces();
    for (auto piece : pieces) {
        action.add_option(make_shared<BitOption>(piece));
    }
}

bool ChoosePieceOnBoard::is_available(shared_ptr<Player> player) {
    shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(_bit_refs[e_board].get()->get_bit(player));
    
    if(board == nullptr) return false;

    const vector<shared_ptr<Piece>> &pieces = board->get_pieces();

    return pieces.size() != 0;
}
