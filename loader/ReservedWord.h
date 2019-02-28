//
// Created by CelitFel on 2019-02-28.
//

#ifndef BGCORE_RESERVEDWORD_H
#define BGCORE_RESERVEDWORD_H

#import <string>
#import <vector>
#include "BGRuleValue.h"

using namespace std;

namespace gameLoader {

    class ReservedWord {
    public:
        ReservedWord(const string& word);
        void Resolve(const string &value, ifstream &bgrulesFile);

    protected:
        string _reservedWord;
        vector<BGRuleValue> _possibleValueTypes;
    };

}


#endif //BGCORE_RESERVEDWORD_H
