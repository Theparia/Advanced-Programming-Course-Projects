#include "Reservation.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

Reservation::Reservation(int id_, Hotel *hotel_, string roomType_, Duration durationOfStay_, vector<Room *> bookedRooms_)
{
    id = id_;
    hotel = hotel_;
    roomType = roomType_;
    durationOfStay = durationOfStay_;
    bookedRooms = bookedRooms_;
}
int Reservation::getNumberOfNightsStay()
{
    return durationOfStay.checkOut - durationOfStay.checkIn + 1;
}
Duration Reservation::getDurationOfStay()
{
    return durationOfStay;
}
double Reservation::getTotalPrice()
{
    double price = (bookedRooms.size()) * hotel->getPrices()[roomType] * getNumberOfNightsStay();
    return price;
}
int Reservation::getId()
{
    return id;
}
string Reservation::getRoomType()
{
    return roomType;
}
vector<Room *> Reservation::getRooms()
{
    return bookedRooms;
}
Hotel *Reservation::getHotel()
{
    return hotel;
}
void Reservation::printInfo()
{
    cout << ID<<COLON<<SPACE << id <<SPACE
         << HOTEL<<COLON<<SPACE << hotel->getUniqueId() << SPACE
         << ROOM<<COLON<<SPACE << roomType << SPACE
         << QUANTITY<<COLON<<SPACE<< bookedRooms.size() << SPACE
         <<COST<<COLON<<SPACE << fixed << setprecision(0) << getTotalPrice() << SPACE
         << CHECK_IN<<SPACE << durationOfStay.checkIn << SPACE
         << CHECK_OUT<<SPACE << durationOfStay.checkOut << endl;
}
void Reservation::cancel()
{
    hotel->deleteReservation(roomType,bookedRooms,durationOfStay);
}