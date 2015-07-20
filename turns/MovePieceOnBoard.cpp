//
// Created by Celito on 7/20/2015.
//

#include "MovePieceOnBoard.h"

MovePieceOnBoard::MovePieceOnBoard(shared_ptr<BitReference> target_board) {
    _bit_refs[board] = target_board;
}
