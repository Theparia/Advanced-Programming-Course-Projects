#ifndef _ROOM_H_
#define _ROOM_H_ "_ROOM_H_"

#include <string>
#include <vector>
#include "StructsAndDefines.hpp"

class Room
{
private:
    std::string type;
    std::string id;

public:
    Room(std::string id_,std::string type_);
    std::string getType();
};

#endif