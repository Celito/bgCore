//
// Created by Celito on 7/20/2015.
//

#include "MovePieceOnBoard.h"

MovePieceOnBoard::MovePieceOnBoard(shared_ptr<BitReference> target_board) : ChoosePieceOnBoard(target_board) {

}

string MovePieceOnBoard::get_description() const {
    return "Move piece on the board";
}
