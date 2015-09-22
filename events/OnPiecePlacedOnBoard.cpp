//
// Created by Celito on 9/21/2015.
//

#include <iostream>
#include "OnPiecePlacedOnBoard.h"
#include "../gameBits/GameBit.h"
#include "../turns/actions/PlacePieceOnBoard.h"
#include "../turns/actions/options/BitOption.h"

OnPiecePlacedOnBoard::OnPiecePlacedOnBoard(shared_ptr<GameBit> tracked_piece, shared_ptr<GameBit> target_board,
       shared_ptr<PlacePieceOnBoard> action_def) : _tracked_piece(tracked_piece), _target_board(target_board)
{
    action_def->on_action_taken(boost::bind(&OnPiecePlacedOnBoard::on_tracked_piece_placed_on_board, this, _1));
    _happened = false;
}

void OnPiecePlacedOnBoard::on_tracked_piece_placed_on_board(shared_ptr<Action> action)
{
    if(_tracked_piece.expired()) throw new exception();
    if(_target_board.expired()) throw new exception();
    auto target_parent_ptr = _target_board.lock();
    shared_ptr<BitOption> opt_ptr = (shared_ptr<BitOption>)dynamic_pointer_cast<BitOption>(action->get_choose_opt());
    if(!_happened && _tracked_piece.lock()->is_child_of(target_parent_ptr) &&
            opt_ptr && opt_ptr->get_bit() == _tracked_piece.lock())
    {
        _happened = true;
        cout << "Reached an \"OnBitPlaced\" event" << endl;
    }
}
