//
// Created by Celito on 2015-07-09.
//

#include "ChooseTileOnBoard.h"
#include "options/TileOption.h"

bool ChooseTileOnBoard::is_available() const {
    //TODO: make it based on the placement rules for the piece if there is one
    return _target->have_free_tiles();
}

void ChooseTileOnBoard::init(shared_ptr<Player> player) {
    Action::init(player);
    _options.clear();
    assert(_target = dynamic_pointer_cast<Board>(_target_ref.get_bit()));
    //TODO: load the options base on the placement rules for the piece
    vector< shared_ptr<Tile> > tiles =  _target.get()->get_available_titles();
    for_each(tiles.begin(), tiles.end(), [this](shared_ptr<Tile> tile){
        _options.push_back(make_shared<TileOption>(tile));
    });
}

string ChooseTileOnBoard::get_description() const {
    return "Choose a board location";
}
