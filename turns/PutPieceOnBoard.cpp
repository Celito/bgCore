//
// Created by Celito on 2015-06-27.
//

#include "PutPieceOnBoard.h"

PutPieceOnBoard::PutPieceOnBoard() {

}

bool PutPieceOnBoard::is_available() {
    return !_piece_set->is_empty() && _board->have_free_tiles();
}
