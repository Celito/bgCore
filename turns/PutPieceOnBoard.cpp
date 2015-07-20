//
// Created by Celito on 2015-06-27.
//

#include "PutPieceOnBoard.h"
#include "ChoosePieceOnSet.h"
#include "options/Option.h"
#include "../gameBits/PieceSet.h"
#include "../gameBits/boards/Board.h"
#include "options/BitOption.h"
#include "ChooseTileOnBoard.h"
#include "options/TileOption.h"

PutPieceOnBoard::PutPieceOnBoard(shared_ptr<BitReference> pieces_pool, shared_ptr<BitReference> target_board) {
    _choose_piece_action = make_shared<ChoosePieceOnSet>(pieces_pool);
    _choose_piece_action->on_option_taken([this](shared_ptr<Option> opt){
        auto bit_opt = dynamic_pointer_cast<BitOption>(opt);
        _selected_bit = bit_opt->get_bit();
        cout << "PIECE SELECTED: " << _selected_bit->get_bit_id() << endl;
    });
    _choose_tile_on_board = make_shared<ChooseTileOnBoard>(target_board);
    _choose_piece_action->set_next_action(_choose_tile_on_board);
    _choose_piece_action->concat_action(_choose_tile_on_board);
    _choose_tile_on_board->on_option_taken([this](shared_ptr<Option> opt){
        auto bit_opt = dynamic_pointer_cast<TileOption>(opt);
        shared_ptr<Tile> selected_tile = bit_opt->get_tile();
        selected_tile->receive(_selected_bit);
        cout << "PIECE: " << _selected_bit->get_bit_id() <<
                " PLACED ON " << selected_tile->get_pos().to_string() << endl;
    });
}

bool PutPieceOnBoard::is_available() const {
    bool ret = _choose_piece_action->is_available();
    //vector< shared_ptr<Option> > options =  _choose_piece_action->get_options();

    return ret;
}

void PutPieceOnBoard::init(shared_ptr<Player> player) {
    Action::init(player);
    _choose_piece_action->init(player);
    set_next_action(_choose_piece_action);

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

void PutPieceOnBoard::update_options() {
    _choose_piece_action->update_options();
}
