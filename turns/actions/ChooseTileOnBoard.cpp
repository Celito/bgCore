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

    shared_ptr<Board> target = (shared_ptr<Board>)dynamic_pointer_cast<Board>(_required_bits[e_board].lock());

    if(!(target != nullptr)) throw;


    //TODO: load the options base on the placement/movement rules for the piece
    vector< shared_ptr<Tile> > tiles;
    
    if(_reason == e_for_placement) {
        tiles = target->get_tiles_for_placement();
        for_each(tiles.begin(), tiles.end(), [this](shared_ptr<Tile> tile){
            _options.push_back(make_shared<TileOption>(tile));
        });
    }
    else if(_reason == e_for_movement){
        assert(_required_bits.count(e_piece) != 0 && !_required_bits[e_piece].expired());
        assert(_required_bits.count(e_tile) != 0 && !_required_bits[e_tile].expired());

        shared_ptr<Tile> last_tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(_required_bits[e_tile].lock());
        shared_ptr<Piece> piece = (shared_ptr<Piece>)dynamic_pointer_cast<Piece>(_required_bits[e_piece].lock());

        _options = target->get_options_for_movement(piece, last_tile);
    }
}
