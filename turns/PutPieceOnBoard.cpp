//
// Created by Celito on 2015-06-27.
//

#include "PutPieceOnBoard.h"
#include "options/Option.h"
#include "../gameBits/PieceSet.h"
#include "../gameBits/boards/Board.h"
#include "options/BitOption.h"
#include "ChooseTileOnBoard.h"
#include "options/TileOption.h"

PutPieceOnBoard::PutPieceOnBoard(shared_ptr<BitReference> pieces_pool, shared_ptr<BitReference> target_board) :
        ChoosePieceOnSet(pieces_pool) {
    on_option_taken([this](shared_ptr<Option> opt){
        auto bit_opt = dynamic_pointer_cast<BitOption>(opt);
        _selected_bit = bit_opt->get_bit();
        cout << "PIECE SELECTED: " << _selected_bit->get_bit_id() << endl;
    });
    _choose_tile_on_board = make_shared<ChooseTileOnBoard>(target_board);
    set_next_action(_choose_tile_on_board);
    concat_action(_choose_tile_on_board);
    _choose_tile_on_board->on_option_taken([this](shared_ptr<Option> opt){
        auto bit_opt = dynamic_pointer_cast<TileOption>(opt);
        shared_ptr<Tile> selected_tile = bit_opt->get_tile();
        selected_tile->receive(_selected_bit);
        cout << "PIECE: " << _selected_bit->get_bit_id() <<
                " PLACED ON " << selected_tile->get_pos().to_string() << endl;
    });
}

string PutPieceOnBoard::get_description() const {
    return "Put a piece on the table";
}

