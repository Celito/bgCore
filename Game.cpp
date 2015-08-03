//
// Created by Celito on 5/27/2015.
//

#include <iostream>
#include <algorithm>
#include <stdint-gcc.h>
#include "Game.h"
#include "GameController.h"
#include "player/Player.h"
#include "BitsManager.h"
#include "gameBits/PieceSet.h"
#include "turns/TurnsManager.h"
#include "turns/TurnDef.h"
#include "turns/actions/ActionDef.h"
#include "gameBits/boards/HexBoard.h"
#include "turns/actions/PutPieceOnBoard.h"
#include "turns/actions/MultiActions.h"
#include "turns/actions/MovePieceOnBoard.h"
#include "rules/PlayerAttrComparison.h"

using namespace std;

Game::Game() {
    cout << "Creating the Game" << endl;

    // Initialize the supporting managers;
    _bits_manager = make_shared<BitsManager>(*this);
    _turns = make_shared<TurnsManager>(*this);
    _attr_manager = make_shared<AttrManager>();

    //TEMP starting to manual load the game configuration
    _num_of_players = 2;
    string PLAYER_PIECES = "PiecesSet";
    string COLOR_ATTR = "Color";
    string HEX_BOARD_NAME = "Table";

    //TEMP vector with the quantity of each piece on the set and its bit id
    vector<pair<uint32_t , string> > pieces_info =
    {
        {1, "Queen"},
        {2, "Beetle"},
        {2, "Spider"},
        {3, "GrassHooper"},
        {3, "Ant"},
    };

    map<string, shared_ptr<MovementFilterRule> > movement_rules;


    shared_ptr<PlayerAttrComparison> is_player_color = make_shared<PlayerAttrComparison>(*this);
    is_player_color->set_tested_attr(COLOR_ATTR);

    movement_rules["Queen"] = make_shared<MovementFilterRule>();
    movement_rules["Queen"]->set_max_steps(1);
    movement_rules["Beetle"] = make_shared<MovementFilterRule>();
    movement_rules["Spider"] = make_shared<MovementFilterRule>();
    movement_rules["Spider"]->set_max_steps(3);
    movement_rules["Spider"]->set_min_steps(3);
    movement_rules["GrassHooper"] = make_shared<MovementFilterRule>();
    movement_rules["Ant"] = make_shared<MovementFilterRule>();

    for (uint32_t i = 0; i < _num_of_players; i++) {

        shared_ptr<Player> player = make_shared<Player>(*this, i+1);
        player->set_attr(COLOR_ATTR, i);
        _players.push_back(player);

        shared_ptr<PieceSet> player_set = make_shared<PieceSet>(*this, PLAYER_PIECES);
        register_new_bit(player_set);

        for(auto iter = pieces_info.begin(); iter != pieces_info.end(); iter++ )
        {
            for(uint32_t j = 0; j < iter->first; j++)
            {
                shared_ptr<Piece> new_piece = make_shared<Piece>(*this, iter->second);
                register_new_bit(new_piece);
                new_piece->set_attr(COLOR_ATTR, i);
                new_piece->add_movement_availability_rule(is_player_color);
                new_piece->add_movement_rule(movement_rules[iter->second]);
                player_set->receive(new_piece);
            }
        }
        _players[i]->receive(player_set);
    }

    // TEMP create the board, call it 'Table' and add it to the table objects;
    shared_ptr<HexBoard> board = make_shared<HexBoard>(*this, HEX_BOARD_NAME);
    register_new_bit(board);
    receive(board);

    // TEMP create the normal turn with the possible actions in it;
    shared_ptr<TurnDef> normal_turn = make_shared<TurnDef>();

    auto put_piece_on_board =
            make_shared<PutPieceOnBoard>(
                    make_shared<BitReference>(PLAYER_PIECES, *this, true),
                    make_shared<BitReference>(HEX_BOARD_NAME, *this)
            );

    //put_piece_on_board->add_enable_movement_rule();

    auto move_piece_on_board =
            make_shared<MovePieceOnBoard>(make_shared<BitReference>(HEX_BOARD_NAME, *this));

    auto first_action = make_shared<MultiActions>();

    first_action->add_sub_action(put_piece_on_board);

    first_action->add_sub_action(move_piece_on_board);

    normal_turn->add_action(first_action);

    _turns->register_turn(normal_turn);

    _is_over = false;

    //TODO: create a sample of rules (hive)

    //TODO: load the game bits

    //TODO: create the turn structure

    //TODO: load the rules

    //TODO: create the group of pieces

    //TODO: create the player inventory
}

void Game::start(GameController &game_controller) {
    for(uint32_t i = 0; i < _players.size(); i++) {
        _players[i]->set_controller(game_controller.get_player_controller(i));
    }

    while(!_is_over) {
        _turns->next_turn();
    }
}

shared_ptr<Player> Game::get_player(uint32_t id) {
    return _players[id];
}

shared_ptr<GameBit> Game::get_table_bit(string bit_id) const {
    vector<weak_ptr<GameBit>>::const_iterator it;
    it = find_if(_bits.begin(), _bits.end(),
                 [bit_id](weak_ptr<GameBit> const& bit) -> bool { return bit.expired()? false : bit.lock()->get_bit_id() == bit_id;});
    return it->expired()? nullptr : it->lock();
}

void Game::register_new_bit(shared_ptr<GameBit> bit) {
    _bits_manager->register_bit(bit);
}
