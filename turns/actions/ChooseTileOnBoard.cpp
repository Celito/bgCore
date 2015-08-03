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

void ChooseTileOnBoard::update_options() {
    _options.clear();

    if(!(_required_bits.count(e_board) != 0 && !_required_bits[e_board].expired())) throw;

    shared_ptr<Board> target_board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(_required_bits[e_board].lock());

    if(target_board == nullptr) throw new exception();
    
    if(_reason == e_for_placement) {
        //TODO: take the rules of placement from the piece and apply them to the options
        vector<shared_ptr<Tile> > tiles = target_board->get_tiles();
        // find all available tiles on the board
        for_each(tiles.begin(), tiles.end(), [this](shared_ptr<Tile> tile){
            if(tile->is_empty()) {
                _options.push_back(make_shared<TileOption>(tile));
            }
        });
    }
    else if(_reason == e_for_movement){
        if(_required_bits[e_piece].expired() || _required_bits.count(e_piece) == 0) throw new exception();
        if(_required_bits[e_tile].expired() || _required_bits.count(e_tile) == 0) throw new exception();

        shared_ptr<Tile> start_tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(_required_bits[e_tile].lock());
        shared_ptr<Piece> piece = (shared_ptr<Piece>)dynamic_pointer_cast<Piece>(_required_bits[e_piece].lock());

        // get all the movement rules and apply them to the options;
        vector< shared_ptr<MovementFilterRule> > movement_rule = piece->get_movement_rules();

        if(movement_rule.size() == 0) throw new exception();

        // apply each of the movement rule at the options;
        for (auto rule : movement_rule) {
            rule->filter_positions(_options, start_tile);
        }
    }
}
