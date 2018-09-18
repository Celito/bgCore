//
// Created by Celito on 2018-09-17.
//

#ifndef BGCORE_MANUALPROPERTY_H
#define BGCORE_MANUALPROPERTY_H

#include <c++/string>

using namespace std;

enum ManualPropertyType {
    Integer,
    Enum,
    ObjectList
};

class ManualProperty
{
public:
    ManualProperty(string & name, ManualPropertyType type);

private:
    string _name;
    ManualPropertyType _type;
};


#endif //BGCORE_MANUALPROPERTY_H
