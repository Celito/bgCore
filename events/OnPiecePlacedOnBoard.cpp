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
    if(opt_ptr == nullptr || opt_ptr->get_bit() == nullptr) return;
    shared_ptr<GameBit> option_piece = opt_ptr->get_bit();
    shared_ptr<GameBit> tracked_piece_ptr = _tracked_piece.lock();
    if(!_happened && tracked_piece_ptr->is_child_of(target_parent_ptr) && option_piece == tracked_piece_ptr)
    {
        _happened = true;
        for(auto game_change : _game_changes)
        {
            game_change->apply();
        }
    }
}
