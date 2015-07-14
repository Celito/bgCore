//
// Created by Celito on 7/14/2015.
//

#include "Tile.h"
#include "Board.h"
#include "TilePos.h"

Tile::Tile(Board &board, TilePos location, vector<TilePos> const &directions) :
        _board(board), _location(location),    _directions(directions), _updating(false) {
    for (int i = 0; i < _directions.size(); ++i) {
        _neighbours.push_back(weak_ptr<Tile>());
    }
}

void Tile::update_neighbourhood(){
    _updating = true;
    for(uint32_t i = 0; i < _directions.size(); i++){
        if(!_neighbours[i].lock()){
            shared_ptr<Tile> other = _board.get_tile(_location + _directions[i]);
            if(other == nullptr){
                _updating = false;
                return;
            }
            _neighbours[i] = other;
        }
        shared_ptr<Tile> neighbour = _neighbours[i].lock();
        if(neighbour && !neighbour->is_updating()) neighbour->update_neighbourhood();
    }
    _updating = false;
}
