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
#include "../../Game.h"
#include "options/TileOption.h"

PutPieceOnBoard::PutPieceOnBoard(Game &game, shared_ptr<BitReference> pieces_pool,
                                 shared_ptr<BitReference> target_board)
        : ChoosePieceOnSet(game, pieces_pool) {
    _choose_tile_on_board = make_shared<ChooseTileOnBoard>(_game, target_board);
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
        selected_tile->receive(_selected_bit);
    });

    next_action->init();

    turn->add_next_action(next_action);

}
