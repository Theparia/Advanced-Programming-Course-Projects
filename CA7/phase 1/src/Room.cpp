#include "Room.hpp"
#include <algorithm>

using namespace std;

void Room::addReservation(Duration duration)
{
    reservations.push_back(duration);
}
Room::Room(string id_, string type_)
{
    id = id_;
    type = type_;
}
string Room::getType()
{
    return type;
}
bool Room::isReservedIn(Duration duration) 
{
    for (auto reservation : reservations)
    {
        if ((reservation.checkIn <= duration.checkIn && reservation.checkOut >= duration.checkIn) ||
            (duration.checkIn<=reservation.checkIn && duration.checkOut>=reservation.checkIn))
            return true;
    }
    return false;
}
string Room::getId()
{
    return id;
}
void Room::cancelBooking(Duration duration)
{
    reservations.erase(find(reservations.begin(), reservations.end(), duration));
}