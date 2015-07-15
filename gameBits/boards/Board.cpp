//
// Created by Celito on 2015-06-27.
//

#include <algorithm>
#include "Board.h"
#include "Tile.h"

vector < shared_ptr<Tile> > Board::get_available_titles() {
    vector< shared_ptr<Tile> > ret;
    for_each(_tile_grid.begin(), _tile_grid.end(), [&ret](pair< TilePos, shared_ptr<Tile> > tile_entry){
        if(tile_entry.second->is_empty()){
            ret.push_back(tile_entry.second);
        }
    });
    return ret;
}
