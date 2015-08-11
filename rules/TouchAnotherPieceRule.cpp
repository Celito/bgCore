//
// Created by Celito on 8/11/2015.
//

#include "TouchAnotherPieceRule.h"
#include "../Game.h"
#include "../gameBits/boards/Tile.h"
#include "../player/Player.h"

bool TouchAnotherPieceRule::test() {
    if(_player.expired()) throw new exception();
    if(_required_bits.count(e_tile) == 0) throw new exception();
    if(_required_bits[e_tile].expired()) throw new exception();
    shared_ptr<Tile> tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(_required_bits[e_tile].lock());

    bool ret = false;
    for (uint32_t i = 0; i < tile->get_num_of_directions(); ++i) {
        shared_ptr<Tile> neighbour = tile->get_neighbour(i);
        if(neighbour == nullptr) continue;
        shared_ptr<Piece> piece = neighbour->get_top_piece();
        if(piece == nullptr) continue;
        ret = true;
        for (auto matching_attr : _matching_attrs_player){
            if(piece->get_attr(matching_attr).get_value() != _player.lock()->get_attr(matching_attr).get_value()){
                ret = false;
                break;
            }
        }
    }
    return _do_not_touch == !ret;
}

void TouchAnotherPieceRule::add_piece_matching_player_attr(string attr) {
    _matching_attrs_player.push_back(_game.get_attr().get()->register_id(attr));
}
