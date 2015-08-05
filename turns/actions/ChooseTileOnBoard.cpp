//
// Created by Celito on 2015-07-09.
//

#include "ChooseTileOnBoard.h"
#include "options/TileOption.h"
#include "../../gameBits/Piece.h"

ChooseTileOnBoard::ChooseTileOnBoard(shared_ptr<BitReference> target) {
    _bit_refs[e_board] = target;
}

string ChooseTileOnBoard::get_description() const {
    return "Choose a board location";
}

void ChooseTileOnBoard::update_options(Action &action) {

    shared_ptr<Board> target_board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(action.get_req_bit(e_board));

    if(target_board == nullptr) throw new exception();
    
    if(_reason == e_for_placement) {
        //TODO: take the rules of placement from the piece and apply them to the options
        vector<shared_ptr<Tile> > tiles = target_board->get_tiles();
        // find all available tiles on the board
        for (auto tile : tiles) {
            if(tile->is_empty()) {
                action.add_option(make_shared<TileOption>(tile));
            }
        }
    }
    else if(_reason == e_for_movement){
        shared_ptr<Tile> start_tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(action.get_req_bit(e_tile));
        shared_ptr<Piece> piece = (shared_ptr<Piece>)dynamic_pointer_cast<Piece>(action.get_req_bit(e_piece));

        if(start_tile == nullptr) throw new exception();
        if(piece == nullptr) throw new exception();

        // get all the movement rules and apply them to the options;
        vector< shared_ptr<MovementFilterRule> > movement_rule = piece->get_movement_rules();

        if(movement_rule.size() == 0) throw new exception();

        vector<shared_ptr<Option>> options;
        // apply each of the movement rule at the options;
        for (auto rule : movement_rule) {
            rule->filter_positions(options, start_tile);
        }

    }
}
