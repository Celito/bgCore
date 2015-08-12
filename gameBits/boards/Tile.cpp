//
// Created by Celito on 7/14/2015.
//

#include <c++/iostream>
#include "Tile.h"

Tile::Tile(Board &board, TilePos location, vector<TilePos> directions) :
        _board(board), _pos(location), _directions(directions),_updating(false),
        GameBit(board.get_game(), board.get_bit_id() + location.to_string()) {}

void Tile::receive(shared_ptr<GameBit> bit) {
    GameBit::receive(bit);
    _piece_received(*this);
}

void Tile::populate_neighbours() {
    for(uint32_t i = 0; i < _directions.size(); i++){
        shared_ptr<Tile> neighbour = get_neighbour(i);
        if(neighbour == nullptr){
            TilePos pos = _pos + _directions[i];
            shared_ptr<Tile> unlink_neighbour = _board.get_tile(pos);
            if(unlink_neighbour == nullptr){
                _board.add_new_tile(pos);
            }
        }
    }
}

shared_ptr<Piece> Tile::get_top_piece() const {
    const vector<weak_ptr<GameBit>> &children = get_children();
    return dynamic_pointer_cast<Piece>(
            children.empty() || children[children.size() - 1].expired()? nullptr : children[children.size() - 1].lock()
    );
}

void Tile::remove(shared_ptr<GameBit> bit) {
    GameBit::remove(bit);
    _piece_removed(*this, *((Piece *)bit.get()));
}

void Tile::clear_neighbours() {
    for(uint32_t i = 0; i < _directions.size(); i++) {
        shared_ptr<Tile> neighbour = get_neighbour(i);
        if(neighbour != nullptr && neighbour->is_empty()){
            bool all_empty = true;
            // test if all neighbours are empty
            for(uint32_t j = 0; j < _directions.size(); j++) {
                shared_ptr<Tile> neighbour2 = neighbour->get_neighbour(j);
                if(neighbour2 != nullptr && !neighbour2->is_empty()){
                    all_empty = false;
                    break;
                }
            }
            if(all_empty){
                _board.remove_tile(neighbour->get_pos());
            }
        }
    }
}
