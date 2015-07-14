//
// Created by Celito on 7/14/2015.
//

#ifndef BGCORE_TILEPOS_H
#define BGCORE_TILEPOS_H

#include <stdint.h>
#include <c++/bits/stl_pair.h>

using namespace std;

class TilePos : public pair<int32_t, int32_t>{
public:
    TilePos(int32_t x, int32_t y);

    TilePos operator+(TilePos const &pos) const;
};


#endif //BGCORE_TILEPOS_H
