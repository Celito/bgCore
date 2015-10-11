//
// Created by Celito on 2015-06-27.
//

#include "PlacePieceOnBoard.h"
#include "options/Option.h"
#include "../../gameBits/PieceSet.h"
#include "../../gameBits/boards/Tile.h"
#include "ChooseTileOnBoard.h"
#include "../Turn.h"
#include "../State.h"
#include "options/TileOption.h"
#include "options/BitOption.h"

PlacePieceOnBoard::PlacePieceOnBoard(BgCore &game, shared_ptr<BitReference> pieces_pool,
    shared_ptr<BitReference> target_board) : ChoosePieceOnSet(game, pieces_pool)
{
    _choose_tile_on_board = make_shared<ChooseTileOnBoard>(_game, target_board);
    _static_next_action = _choose_tile_on_board;
    _can_pre_process = true;
}

string PlacePieceOnBoard::get_description() const
{
    return "Put a piece on the table";
}

void PlacePieceOnBoard::process_choice(shared_ptr<Action> action)
{
    ActionDef::process_choice(action);

    auto option = action->get_choose_opt();
    auto bit_option = dynamic_pointer_cast<BitOption>(option);
    auto next_action = option->get_pre_processed_next_action();
    auto selected_bit = bit_option->get_bit();

    next_action->on_option_taken
    (
         [this, action, selected_bit](shared_ptr<Option> opt)
         {
             auto tile_option = dynamic_pointer_cast<TileOption>(opt);
             shared_ptr<Tile> selected_tile = tile_option->get_tile();
             //selected_piece->get_game().curr_state()->transfer(selected_tile, _selected_bit);
             selected_tile->receive(selected_bit);
             cout << "PIECE: " << selected_bit->get_bit_id() <<
             " PLACED ON " << selected_tile->get_pos().to_string() << endl;
             _action_taken(action);
         }
    );
}
