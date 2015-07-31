//
// Created by Celito on 2015-07-14.
//

#ifndef BGCORE_TILEOPTION_H
#define BGCORE_TILEOPTION_H

#include <vector>
#include "Option.h"

class Tile;

using namespace std;

class TileOption : public Option {
public:
    TileOption(shared_ptr<Tile> tile) : _tile(tile) {}

    virtual string get_description() override;

    shared_ptr<Tile> get_tile() const { return _tile.expired() ? nullptr : _tile.lock(); }

    vector< weak_ptr<Tile> > get_path() { return _path; }

    void add_path_node(weak_ptr<Tile> item) { _path.push_back(item); }
    void concat_path(vector<weak_ptr<Tile> >  const &other_path);

private:
    weak_ptr<Tile> _tile;
    vector< weak_ptr<Tile> > _path;
};


#endif //BGCORE_TILEOPTION_H
