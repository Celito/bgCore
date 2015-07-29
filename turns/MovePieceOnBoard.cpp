//
// Created by Celito on 7/20/2015.
//

#include <c++/iostream>
#include "MovePieceOnBoard.h"
#include "options/BitOption.h"
#include "options/TileOption.h"

MovePieceOnBoard::MovePieceOnBoard(shared_ptr<BitReference> target_board) : ChoosePieceOnBoard(target_board) {
    _choose_tile_on_board = make_shared<ChooseTileOnBoard>(target_board);
    _choose_tile_on_board->set_reason(e_for_movement);
    set_next_action(_choose_tile_on_board);
    concat_action(_choose_tile_on_board);
    on_option_taken([this](shared_ptr<Option> opt){
        auto bit_opt = dynamic_pointer_cast<BitOption>(opt);
        _selected_bit = bit_opt->get_bit();
        _choose_tile_on_board->set_required_bit(e_piece, _selected_bit);

        assert(dynamic_pointer_cast<Tile>(_selected_bit->get_parent()));

        shared_ptr<Tile> tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(_selected_bit->get_parent());
        _choose_tile_on_board->set_required_bit(e_tile, tile);
        _curr_player->receive(_selected_bit);
    });
    _choose_tile_on_board->on_option_taken([this](shared_ptr<Option> opt){
        auto tile_opt = dynamic_pointer_cast<TileOption>(opt);
        shared_ptr<Tile> tile = tile_opt->get_tile();
        tile->receive(_selected_bit);
        cout << "PIECE " << _selected_bit->get_unique_id() << " MOVED TO " << tile->get_pos().to_string() << endl;
    });
}

string MovePieceOnBoard::get_description() const {
    return "Choose a piece to move on the board";
}

void MovePieceOnBoard::update_options() {
    _options.clear();

    assert(_required_bits.count(e_board) != 0 && !_required_bits[e_board].expired());

    shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(_required_bits[e_board].lock());

    if(!(board != nullptr)) throw;

    vector< shared_ptr<Piece> > pieces = board.get()->get_available_pieces(_curr_player);
    for (auto piece : pieces) {
        _options.push_back(make_shared<BitOption>(piece));
    }
}
