//
// Created by Celito on 2015-06-27.
//

#include "PutPieceOnBoard.h"
#include "options/Option.h"
#include "../../gameBits/PieceSet.h"
#include "../../gameBits/boards/Tile.h"
#include "options/BitOption.h"
#include "ChooseTileOnBoard.h"
#include "../Turn.h"
#include "../State.h"
#include "../../Game.h"
#include "options/TileOption.h"

PutPieceOnBoard::PutPieceOnBoard(shared_ptr<BitReference> pieces_pool, shared_ptr<BitReference> target_board) :
        ChoosePieceOnSet(pieces_pool) {
    _choose_tile_on_board = make_shared<ChooseTileOnBoard>(target_board);
}

string PutPieceOnBoard::get_description() const {
    return "Put a piece on the table";
}

void PutPieceOnBoard::choose(Action &action) {
    ActionDef::choose(action);
    auto bit_opt = dynamic_pointer_cast<BitOption>(action.get_choose_opt());
    _selected_bit = bit_opt->get_bit();
    shared_ptr<Piece> selected_piece = (shared_ptr<Piece>)dynamic_pointer_cast<Piece>(bit_opt->get_bit());

    shared_ptr<Turn> turn = action.get_turn();

    const shared_ptr<Action> &next_action = make_shared<Action>(turn, _choose_tile_on_board);

    next_action->add_req_bit(e_piece, selected_piece);

    next_action->on_option_taken([this](shared_ptr<Option> opt){
        auto tile_option = dynamic_pointer_cast<TileOption>(opt);
        shared_ptr<Tile> selected_tile = tile_option->get_tile();
        //selected_piece->get_game().curr_state()->transfer(selected_tile, _selected_bit);
        selected_tile->receive(_selected_bit);
        cout << "PIECE: " << _selected_bit->get_bit_id() <<
            " PLACED ON " << selected_tile->get_pos().to_string() << endl;
    });

    next_action->init();

    turn->add_next_action(next_action);

}
