#include "Room.hpp"
#include <algorithm>

using namespace std;

Room::Room(string id_, string type_)
{
    id = id_;
    type = type_;
}
string Room::getType()
{
    return type;
}
