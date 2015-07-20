//
// Created by Celito on 7/14/2015.
//

#include "Tile.h"
#include "Board.h"
#include "TilePos.h"

Tile::Tile(Board &board, TilePos location, vector<TilePos> directions) :
        _board(board), _pos(location), _directions(directions),_updating(false), GameBit(board.get_game(), board.get_bit_id() + location.to_string()) {
    for (int i = 0; i < _directions.size(); ++i) {
        _neighbours.push_back(weak_ptr<Tile>());
    }
}

void Tile::update_neighbourhood(shared_ptr<Tile> self){
    for(uint32_t i = 0; i < _directions.size(); i++){
        shared_ptr<Tile> neighbour = get_neighbour(i);
        if(neighbour == nullptr){
            shared_ptr<Tile> other = _board.get_tile(_pos + _directions[i]);
            if(other == nullptr){
                return;
            }
            set_neighbour(i, other);
        }
        neighbour = get_neighbour(i);

        neighbour->set_neighbour((i + _directions.size() / 2) % _directions.size(), self);
    }
}

void Tile::receive(shared_ptr<GameBit> bit) {
    BitHolder::receive(bit);
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
                unlink_neighbour = _board.get_tile(pos);
                unlink_neighbour->update_neighbourhood(unlink_neighbour);
            }
            set_neighbour(i, _board.get_tile(pos));
        }
    }
}

shared_ptr<Piece> Tile::get_top_piece() const {
    return dynamic_pointer_cast<Piece>(_bits.empty()? nullptr : _bits[_bits.size() - 1]);
}
