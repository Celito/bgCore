//
// Created by Celito on 2015-06-27.
//

#include "PutPieceOnBoard.h"
#include "../gameBits/PieceSet.h"
#include "../gameBits/boards/Board.h"

bool PutPieceOnBoard::is_available() const {
    return _pieces_pool && !_pieces_pool->is_empty() && _target_board->have_free_tiles();
}

void PutPieceOnBoard::init(shared_ptr<Player> player) {
    Action::init(player);
    _pieces_pool = dynamic_pointer_cast<PieceSet>(_pieces_pool_ref.get_from_player(player));
    _target_board = dynamic_pointer_cast<Board>(_target_board_ref.get_from_table(player->get_curr_game()));
//    _pieces_pool = _pieces_pool_ref.get_from_player(player);
//    _target_board = _target_board_ref.get_from_table(player->get_curr_game());
    // TODO: assert if the _target_board exists, the _pieces_pool can be null;
}

string PutPieceOnBoard::get_description() const {
    return "Put a piece on the table";
}

void PutPieceOnBoard::choose(shared_ptr<Option> option) {

}
