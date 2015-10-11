//
// Created by Celito on 7/20/2015.
//

#include <iostream>
#include "MovePieceOnBoard.h"
#include "../../gameBits/boards/Board.h"
#include "../../gameBits/boards/Tile.h"
#include "../../gameBits/Piece.h"
#include "options/BitOption.h"
#include "../Turn.h"
#include "../State.h"
#include "../../rules/PlayerAttrComparison.h"
#include "../../rules/RulesManager.h"
#include "options/TileOption.h"
#include "ChooseTileOnBoard.h"

MovePieceOnBoard::MovePieceOnBoard(BgCore &game, shared_ptr<BitReference> target_board) :
    ChoosePieceOnBoard(game, target_board)
{
    _choose_tile_on_board = make_shared<ChooseTileOnBoard>(_game, target_board);
    _choose_tile_on_board->set_reason(e_for_movement);
    _static_next_action = _choose_tile_on_board;
    _can_pre_process = true;
}

string MovePieceOnBoard::get_description() const
{
    return "Choose a piece to move on the board";
}

void MovePieceOnBoard::update_options(Action &action)
{

    shared_ptr<Board> board = (shared_ptr<Board>) dynamic_pointer_cast<Board>(action.get_req_bit(e_board));

    if (board == nullptr) { throw new exception(); }

    const vector<weak_ptr<GameBit>> &tiles = board->get_children();

    for (auto tile_bit_ptr : tiles)
    {
        if (tile_bit_ptr.expired()) { continue; }
        shared_ptr<Tile> tile = (shared_ptr<Tile>) dynamic_pointer_cast<Tile>(tile_bit_ptr.lock());
        shared_ptr<Piece> piece = tile->get_top_piece();
        if (piece == nullptr) { continue; }
        const vector<shared_ptr<Rule>> &rules =
            piece->get_game().rules_manager()->get_rules(e_movement_enable_rule, piece->get_bit_id());
        bool can_be_moved = true;
        for (auto rule_ptr : rules)
        {
            shared_ptr<TestableRule> enable_to_move = dynamic_pointer_cast<TestableRule>(rule_ptr);
            enable_to_move->add_req_bit(e_piece, piece);
            enable_to_move->add_req_bit(e_tile, tile);
            can_be_moved &= enable_to_move->test();
            if (!can_be_moved) { break; }
        }
        if (!can_be_moved)
        {
            continue;
        }
        else
        {
            //TODO: test if there are available spots for that piece to move;
            action.add_option(make_shared<BitOption>(piece));
        }
    }
}

void MovePieceOnBoard::process_choice(shared_ptr<Action> action)
{
    ActionDef::process_choice(action);

    auto option = action->get_choose_opt();
    auto bit_option = dynamic_pointer_cast<BitOption>(option);
    auto next_action = option->get_pre_processed_next_action();
    auto selected_bit = bit_option->get_bit();

    next_action->on_option_taken([this, selected_bit](shared_ptr<Option> opt)
    {
        if (selected_bit == nullptr) { throw new exception(); }
        auto tile_opt = dynamic_pointer_cast<TileOption>(opt);
        shared_ptr<Tile> new_tile = tile_opt->get_tile();
        new_tile->receive(selected_bit);
        cout << "PIECE " << selected_bit->get_bit_id() << " MOVED TO " << new_tile->get_pos().to_string() << endl;
    });
}

bool MovePieceOnBoard::is_available(shared_ptr<Player> player)
{
    shared_ptr<Board>
        board = (shared_ptr<Board>) dynamic_pointer_cast<Board>(_bit_refs[e_board].get()->get_bit(player));
    if (board == nullptr) { return false; }

    const vector<weak_ptr<GameBit>> &tiles = board->get_children();

    bool movable_piece_found = false;

    for (auto tile_bit_ptr : tiles)
    {
        if (tile_bit_ptr.expired()) { continue; }
        shared_ptr<Tile> tile = (shared_ptr<Tile>) dynamic_pointer_cast<Tile>(tile_bit_ptr.lock());
        const shared_ptr<Piece> &piece = tile->get_top_piece();
        if (piece == nullptr) { continue; }
        const vector<shared_ptr<Rule>> &rules =
            piece->get_game().rules_manager()->get_rules(e_movement_enable_rule, piece->get_bit_id());
        bool can_be_moved = true;
        for (auto rule_ptr : rules)
        {
            shared_ptr<TestableRule> enable_to_move = dynamic_pointer_cast<TestableRule>(rule_ptr);
            enable_to_move->add_req_bit(e_piece, piece);
            enable_to_move->add_req_bit(e_tile, tile);
            enable_to_move->set_curr_player(player);
            if (!enable_to_move->test())
            {
                can_be_moved = false;
                break;
            }
        }
        if (can_be_moved)
        {
            //TODO: test if there are available spots for that piece to move;
            movable_piece_found = true;
            break;
        }
    }

    return movable_piece_found;
}

void MovePieceOnBoard::init_by_option(shared_ptr<Action> action, shared_ptr<Option> selected_option)
{
    ActionDef::init_by_option(action, selected_option);
}
