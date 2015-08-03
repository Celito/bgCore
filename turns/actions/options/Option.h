//
// Created by Celito on 7/3/2015.
//

#ifndef BGCORE_OPTION_H
#define BGCORE_OPTION_H

#include <memory>

using  namespace std;

class Option {
public:
    virtual string get_description() = 0;
};


#endif //BGCORE_OPTION_H
