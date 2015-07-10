//
// Created by Celito on 2015-06-27.
//

#include "PutPieceOnBoard.h"
#include "ChoosePiece.h"
#include "options/Option.h"
#include "../gameBits/PieceSet.h"
#include "../gameBits/boards/Board.h"
#include "options/BitOption.h"
#include "MoveBitTo.h"

PutPieceOnBoard::PutPieceOnBoard(BitReference pieces_pool, BitReference target_board) :
        _target_board_ref(target_board) {
    _choose_piece_action = make_shared<ChoosePiece>(pieces_pool);
    _choose_piece_action.get()->on_option_taken([this](shared_ptr<Option> opt){
        shared_ptr<BitOption> bit_opt = dynamic_pointer_cast<BitOption>(opt);
        _selected_bit = bit_opt->get_bit();
        cout << "PIECE SELECTED: " << _selected_bit->get_bit_id() << endl;
    });
    _choose_target_on_board = make_shared<MoveBitTo>(target_board);
    _choose_piece_action->set_next_action(_choose_target_on_board);
}

bool PutPieceOnBoard::is_available() const {
    return _choose_piece_action->is_available() && _target_board->have_free_tiles();
}

void PutPieceOnBoard::init(shared_ptr<Player> player) {
    Action::init(player);
    _choose_piece_action->init(player);
    set_next_action(_choose_piece_action);
    _target_board = dynamic_pointer_cast<Board>(_target_board_ref.get_from_table());
//    _pieces_pool = _pieces_pool_ref.get_from_player(player);
//    _target_board = _target_board_ref.get_from_table(player->get_curr_game());
    // TODO: assert if the _target_board exists, the _pieces_pool can be null;
}

string PutPieceOnBoard::get_description() const {
    return "Put a piece on the table";
}

bool PutPieceOnBoard::self_resolve() {
    return true;
}
