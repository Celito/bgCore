//
// Created by Celito on 8/11/2015.
//

#include "TouchAnotherPieceRule.h"
#include "../Game.h"
#include "../gameBits/attributes/AttrManager.h"
#include "../gameBits/boards/Tile.h"
#include "../gameBits/Piece.h"
#include "../player/Player.h"

bool TouchAnotherPieceRule::test() {
    if(_player.expired()) throw new exception();
    if(_required_bits.count(e_tile) == 0) throw new exception();
    if(_required_bits[e_tile].expired()) throw new exception();
    shared_ptr<Tile> tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(_required_bits[e_tile].lock());

    bool touching = false;
    for (uint32_t i = 0; i < tile->get_num_of_directions(); ++i) {
        shared_ptr<Tile> neighbour = tile->get_neighbour(i);
        if(neighbour == nullptr) continue;
        shared_ptr<Piece> piece = neighbour->get_top_piece();
        if(piece == nullptr) continue;
        touching = true;
        for (auto matching_attr_entry : _compared_attrs_player){
            uint32_t piece_attr = piece->get_attr(matching_attr_entry.first).get_value();
            uint32_t player_attr = _player.lock()->get_attr(matching_attr_entry.first).get_value();
            bool match = piece_attr == player_attr;
            bool have_to_match = matching_attr_entry.second;
            if((match && !have_to_match) || (!match && have_to_match)){
                touching = false;
                break;
            }
        }
        if(touching) break;
    }
    bool result = _do_not_touch == !touching;
    _required_bits.clear();
    return result;
}

void TouchAnotherPieceRule::add_compared_player_attr(string attr, bool have_to_match) {
    uint32_t attr_id = _game.attr_manager()->register_id(attr);
    _compared_attrs_player.push_back(pair<uint32_t, bool>(attr_id, have_to_match));
}
