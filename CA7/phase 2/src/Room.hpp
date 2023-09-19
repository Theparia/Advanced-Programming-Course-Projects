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
    std::vector<Duration> reservations;

public:
    Room(std::string id_,std::string type_);
    void addReservation(Duration duration);
    bool isReservedIn(Duration duration);
    void cancelBooking(Duration duration);
    std::string getId();
    std::string getType();
};

#endif