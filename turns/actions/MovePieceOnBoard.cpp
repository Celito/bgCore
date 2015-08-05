//
// Created by Celito on 7/20/2015.
//

#include <c++/iostream>
#include "MovePieceOnBoard.h"
#include "../../gameBits/boards/Tile.h"
#include "options/BitOption.h"
#include "../Turn.h"

MovePieceOnBoard::MovePieceOnBoard(shared_ptr<BitReference> target_board) : ChoosePieceOnBoard(target_board) {
    _choose_tile_on_board = make_shared<ChooseTileOnBoard>(target_board);
    _choose_tile_on_board->set_reason(e_for_movement);
}

string MovePieceOnBoard::get_description() const {
    return "Choose a piece to move on the board";
}

void MovePieceOnBoard::update_options(Action &action) {

    shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(action.get_req_bit(e_board));

    if(board == nullptr) throw new exception();

    vector< shared_ptr<Piece> > pieces = board.get()->get_available_pieces(_curr_player);
    for (auto piece : pieces) {
        action.add_option(make_shared<BitOption>(piece));
    }
}

void MovePieceOnBoard::choose(Action &action) {
    ActionDef::choose(action);

    auto bit_opt = dynamic_pointer_cast<BitOption>(action.get_choose_opt());
    shared_ptr<GameBit> selected_bit = bit_opt->get_bit();

    if(!(dynamic_pointer_cast<Tile>(selected_bit->get_parent()))) throw new exception();

    shared_ptr<Turn> turn = action.get_turn();

    shared_ptr<Tile> tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(selected_bit->get_parent());
    turn->get_player()->receive(selected_bit);

    shared_ptr<Action> next_action = make_shared<Action>(turn, _choose_tile_on_board );

    next_action->add_req_bit(e_tile, tile);
    next_action->add_req_bit(e_piece, selected_bit);

    next_action->on_option_taken([this, &selected_bit](shared_ptr<Option> opt){
        auto tile_opt = dynamic_pointer_cast<TileOption>(opt);
        shared_ptr<Tile> new_tile = tile_opt->get_tile();
        new_tile->receive(selected_bit);
        cout << "PIECE " << _selected_bit->get_unique_id() << " MOVED TO " << new_tile->get_pos().to_string() << endl;
    });

    turn->add_next_action(next_action);
}
