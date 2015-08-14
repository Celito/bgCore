//
// Created by Celito on 8/14/2015.
//

#ifndef BGCORE_MOVEMENTSUBRULE_H
#define BGCORE_MOVEMENTSUBRULE_H

#include <memory>

class TileOption;

using namespace std;

class MovementSubRule {
public:
    virtual bool opt_can_be_processed(const shared_ptr<TileOption> &analyzed_option) { return true; }
};


#endif //BGCORE_MOVEMENTSUBRULE_H
