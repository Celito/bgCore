//
// Created by Celito on 2015-06-27.
//

#include <memory>
#include <iomanip>
#include <c++/iostream>
#include <algorithm>
#include <c++/sstream>
#include "PlayerTUI.h"
#include "../gameBits/boards/Tile.h"
#include "../turns/actions/Action.h"
#include "../turns/actions/ChooseTileOnBoard.h"
#include "../turns/actions/options/Option.h"
#include "../turns/actions/options/TileOption.h"

void PlayerTUI::resolve_action(shared_ptr<Action> action) {
    //system("cls");
    vector<shared_ptr<Option>> const &options = action->get_options();
    if(action->get_type() == e_choose_tile) {
        shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(action->get_req_bit(e_board));
        if(board != nullptr){
            print_board(options, board);
        }
    }
    cout << action->get_description() << ":" << endl;
    for (int i = 0; i < options.size(); ++i) {
        cout << i << ") " << options[i]->get_description() << endl;
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
        while(lines.size() <= j) lines.push_back("");
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
            string name = piece->get_bit_id();
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
    for (int k = 0; k < lines.size(); ++k) {
        cout << lines[k] << endl;
    }
}
