//
// Created by Celito on 2015-07-14.
//

#ifndef BGCORE_TILEOPTION_H
#define BGCORE_TILEOPTION_H


#include "Option.h"
#include "../../gameBits/boards/Tile.h"

using namespace std;

class TileOption : public Option {
public:
    TileOption(shared_ptr<Tile> tile) : _tile(tile) {}

    virtual string get_description() override;

    shared_ptr<Tile> get_tile() const { return _tile; }

private:
    shared_ptr<Tile> _tile;
};


#endif //BGCORE_TILEOPTION_H
