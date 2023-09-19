#ifndef _RESERVATION_H_
#define _RESERVATION_H_ "_RESERVATION_H_"

#include <string>
#include <vector>
#include "Hotel.hpp"

class Reservation
{
private:
    int id;
    Hotel *hotel;
    std::string roomType;
    Duration durationOfStay;
    std::vector<Room *> bookedRooms;

public:
    Reservation(int id_, Hotel *hotel_, std::string roomType_, Duration durationOfStay_, std::vector<Room *> bookedRooms_);
    int getId();
    Hotel *getHotel();
    std::string getRoomType();
    Duration getDurationOfStay();
    std::vector<Room *> getRooms();
    double getTotalPrice();
    void printInfo();
    int getNumberOfNightsStay();
    void cancel();
};

#endif