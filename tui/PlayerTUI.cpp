//
// Created by Celito on 2015-06-27.
//

#include <memory>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "PlayerTUI.h"
#include "../gameBits/boards/Tile.h"
#include "../gameBits/Piece.h"
#include "../turns/actions/Action.h"
#include "../turns/actions/ChooseTileOnBoard.h"
#include "../turns/actions/options/Option.h"
#include "../turns/actions/options/TileOption.h"
#include "../player/PlayerInterface.h"

/**
 * Receive the action from the bg core, display them in the console, waits for a player entry with the choose option and
 * set the chose option on the action before sending the control of the thread back to the core. If the chosen option
 * have a preprocessed action attached to it, the process repeats until there are no more pre processed actions to be
 * made by the player;
 */
void PlayerTUI::resolve_action(shared_ptr<Action> action) {
    //system("cls");
    //TODO: Make the TUI use the pre processed actions;

    shared_ptr<PlayerInterface> my_player = get_interface().lock();
    cout << "============ " << (my_player->get_id() == 1? "-WHITE-" : "<BLACK>") << " PLAYER TURN =============" << endl;
    vector<shared_ptr<Option>> const &options = action->get_options();
    print_opts(action, options);
    if(action->get_type() == e_action_type_choose_tile_on_board) {
        shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(action->get_req_bit(e_board));
        if(board != nullptr){
            cout << "=======================================================" << endl;
            print_board(options, board);
        }
    }
    int32_t option_id = _gameTUI.get_next_pre_loaded_option();
    if(option_id == -1) {
        while (!(cin >> option_id) || option_id >= options.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.  Try again: ";
        }
    }
    else {
        cout << option_id << endl;
    }
    action->choose(options[option_id]);
}

void PlayerTUI::print_opts(const shared_ptr<Action> &action, const vector<shared_ptr<Option>> &options) const {
    cout << action->get_description() << ":" << endl;
    queue<string> opts_str;
    uint16_t biggest_opt_str = 0;
    for (const auto &option : options)
    {
        const string &opt_str = option->get_description();
        if(opt_str.size() > biggest_opt_str) biggest_opt_str = (uint16_t) opt_str.size();
        opts_str.push(opt_str);
    }
    auto opts_size = (uint16_t) (biggest_opt_str + 6);
    const int max_per_line = 79;
    auto opts_per_line = (uint16_t) (max_per_line / opts_size);
    auto chars_left = (uint16_t) (max_per_line - (opts_per_line * (biggest_opt_str + 6)));
    auto lines = (uint16_t) ((opts_str.size() / opts_per_line) + 1);
    uint16_t k = 0;
    for (int j = 0; j < lines; ++j) {
        for (int i = 0; i < opts_per_line && !opts_str.empty(); ++i) {
            cout << k << ") ";
            k++;
            cout.width(biggest_opt_str + 3 + (chars_left / opts_per_line));
            cout << left << opts_str.front();
            opts_str.pop();
            cout.width(0);
        }
        cout << endl;
    }
}

void PlayerTUI::print_board(const vector<shared_ptr<Option>> &options, const shared_ptr<Board> &board) const {
    vector< shared_ptr<Tile> > tiles = board.get()->get_tiles();
    sort(tiles.begin(), tiles.end(),
        [](const shared_ptr<Tile> &t1, const shared_ptr<Tile> &t2) -> bool {
            return t1->y() == t2->y() ? t1->x() < t2->x() : t1->y() > t2->y();
        });
    vector<string> lines;
    int curr_x = tiles[0]->x();
    int min_x = curr_x;
    int curr_y = tiles[0]->y();
    map<uint32_t, map<string, uint32_t> > pieces_count;

    for (int i = 0, j = 0; i < tiles.size(); ++i) {
        shared_ptr<Tile> tile = tiles[i];
        bool new_line = false;
        if(curr_y != tile->y()){
            new_line = true;
            j += curr_y - tile->y();
            curr_y = tile->y();
        }
        while(lines.size() <= j) lines.emplace_back("");
        if(new_line){
            for (int k = 0; k < tile->x() - min_x; ++k) {
                lines[j] += "    ";
            }
        }
        while(curr_x < (tile->x() - 1)){
            lines[j] += "    ";
            curr_x++;
        }
        curr_x = tile->x();
        if(min_x > curr_x){
            for (int k = 0; k < lines.size() - 1; ++k) {
                for (int l = 0; l < min_x - curr_x; ++l) {
                    lines[k] = "    " + lines[k];
                }
            }
            min_x = curr_x;
        }
        if(tile->is_empty()){
            int opt_num = -1;
            for (int k = 0; k < options.size(); ++k) {
                if(auto tile_opt = dynamic_cast<TileOption *>(options[k].get())){
                    if(tile_opt != nullptr && tile_opt->get_tile() == tile){
                        opt_num = k;
                    }
                }
            }
            if(opt_num == -1){
                lines[j] += "[  ]";
            }
            else {
                stringstream a;
                a << setfill(' ') << setw(2) << opt_num;
                lines[j] += "[" + a.str() + "]";
            }
        }
        else {
            shared_ptr<Piece> piece = tile->get_top_piece();
            uint32_t color = piece->get_attr("Color").get_value();
            string name = piece->get_bit_name();
            if(pieces_count[color].count(name) == 0) pieces_count[color][name] = 0;
            else pieces_count[color][name]++;
            uint32_t id = pieces_count[color][name];
            string short_name = name.substr(0, 1) + to_string(id);
            if(color == 0){
                lines[j] += "-" + short_name  + "-";
            }
            else {
                lines[j] += "<" + short_name  + ">";
            }
        }
    }
    for (const auto &line : lines)
    {
        cout << line << endl;
    }
}
