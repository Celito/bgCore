//
// Created by Celito on 7/20/2015.
//

#include <c++/iostream>
#include "MovePieceOnBoard.h"
#include "../../gameBits/boards/Tile.h"
#include "options/BitOption.h"
#include "../Turn.h"
#include "../../rules/PlayerAttrComparison.h"
#include "options/TileOption.h"

MovePieceOnBoard::MovePieceOnBoard(shared_ptr<BitReference> target_board) : ChoosePieceOnBoard(target_board) {
    _choose_tile_on_board = make_shared<ChooseTileOnBoard>(target_board);
    _choose_tile_on_board->set_reason(e_for_movement);
}

string MovePieceOnBoard::get_description() const {
    return "Choose a piece to move on the board";
}

void MovePieceOnBoard::update_options(Action &action) {

    shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(action.get_req_bit(e_board));

    if(board == nullptr) throw new exception();

    const vector<weak_ptr<GameBit>> &tiles = board->get_children();

    for (auto tile_bit_ptr : tiles) {
        if (tile_bit_ptr.expired()) continue;
        shared_ptr<Tile> tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(tile_bit_ptr.lock());
        const shared_ptr<Piece> &piece = tile->get_top_piece();
        if(piece == nullptr) continue;
        const vector<shared_ptr<TestableRule>> &rules = piece->get_availability_for_movement_rules();
        bool can_be_moved = true;
        for (auto enable_to_move_rule : rules) {
            enable_to_move_rule->add_req_bit(e_piece, piece);
            can_be_moved &= enable_to_move_rule.get()->test();
            if(!can_be_moved) break;
        }
        if(!can_be_moved){
            continue;
        }
        else {
            //TODO: test if there are available spots for that piece to move;
            action.add_option(make_shared<BitOption>(piece));
        }
    }
}

void MovePieceOnBoard::choose(Action &action) {
    ActionDef::choose(action);

    auto bit_opt = dynamic_pointer_cast<BitOption>(action.get_choose_opt());
    shared_ptr<GameBit> selected_bit = bit_opt->get_bit();

    if(!(dynamic_pointer_cast<Tile>(selected_bit->get_parent()))) throw new exception();

    shared_ptr<Turn> turn = action.get_turn();

    shared_ptr<Tile> tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(selected_bit->get_parent());
    turn->get_player()->receive(selected_bit);

    shared_ptr<Action> next_action = make_shared<Action>(turn, _choose_tile_on_board );

    next_action->add_req_bit(e_tile, tile);
    next_action->add_req_bit(e_piece, selected_bit);

    next_action->on_option_taken([this, selected_bit](shared_ptr<Option> opt){
        if(selected_bit == nullptr) throw new exception();
        auto tile_opt = dynamic_pointer_cast<TileOption>(opt);
        shared_ptr<Tile> new_tile = tile_opt->get_tile();
        new_tile->receive(selected_bit);
        cout << "PIECE " << selected_bit->get_bit_id() << " MOVED TO " << new_tile->get_pos().to_string() << endl;
    });

    next_action->init();

    turn->add_next_action(next_action);
}

bool MovePieceOnBoard::is_available(shared_ptr<Player> player) {
    shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(_bit_refs[e_board].get()->get_bit(player));
    if(board == nullptr) return false;

    const vector<weak_ptr<GameBit>> &tiles = board->get_children();

    bool movable_piece_found = false;

    for (auto tile_bit_ptr : tiles) {
        if(tile_bit_ptr.expired()) continue;
        shared_ptr<Tile> tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(tile_bit_ptr.lock());
        const shared_ptr<Piece> &piece = tile->get_top_piece();
        if(piece == nullptr) continue;
        const vector<shared_ptr<TestableRule>> &rules = piece->get_availability_for_movement_rules();
        bool can_be_moved = true;
        for (auto enable_to_move_rule : rules) {
            enable_to_move_rule->add_req_bit(e_piece, piece);
            enable_to_move_rule->set_curr_player(player);
            can_be_moved &= enable_to_move_rule.get()->test();
            if(!can_be_moved) break;
        }
        if(!can_be_moved){
            continue;
        }
        else {
            //TODO: test if there are available spots for that piece to move;
            movable_piece_found = true;
            break;
        }
    }

    return movable_piece_found;
}
