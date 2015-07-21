//
// Created by Celito on 7/20/2015.
//

#include "MovePieceOnBoard.h"
#include "options/BitOption.h"

MovePieceOnBoard::MovePieceOnBoard(shared_ptr<BitReference> target_board) : ChoosePieceOnBoard(target_board) {

}

string MovePieceOnBoard::get_description() const {
    return "Move piece on the board";
}


void MovePieceOnBoard::add_enable_movement_rule(shared_ptr<EnableMovementRule> rule) {
    _enable_movement_rules.push_back(rule);
}

void MovePieceOnBoard::update_options() {
    _options.clear();
    shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(_required_bits[e_board]);

    if(board == nullptr) return;

    vector< shared_ptr<Piece> > pieces = board.get()->get_pieces();
    for (auto piece : pieces) {
        _options.push_back(make_shared<BitOption>(piece));
    }
}
