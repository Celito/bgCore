//
// Created by Celito on 2015-07-09.
//

#include "ChooseTileOnBoard.h"
#include "options/TileOption.h"

ChooseTileOnBoard::ChooseTileOnBoard(shared_ptr<BitReference> target) {
    _bit_refs[e_board] = target;
}

string ChooseTileOnBoard::get_description() const {
    return "Choose a board location";
}

void ChooseTileOnBoard::update_options() {
    _options.clear();

    shared_ptr<Board> target = (shared_ptr<Board>)dynamic_pointer_cast<Board>(_required_bits[e_board]);

    if(target == nullptr) return;

    //TODO: load the options base on the placement rules for the piece
    vector< shared_ptr<Tile> > tiles =  target.get()->get_available_titles();
    for_each(tiles.begin(), tiles.end(), [this](shared_ptr<Tile> tile){
        _options.push_back(make_shared<TileOption>(tile));
    });
}
