#include "Hotel.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Exception.hpp"

using namespace std;

Hotel::Hotel(string uniqueId_, string propertyName_, int starRating_, string overview_, string propertyAmenities_, string city_, double latitude_,
             double logitude_, string imageUrl_, vector<Room *> rooms_)

{
    uniqueId = uniqueId_;
    propertyName = propertyName_;
    starRating = starRating_;
    overview = overview_;
    propertyAmenities = propertyAmenities_;
    city = city_;
    latitude = latitude_;
    longitude = logitude_;
    imageUrl = imageUrl_;
    rooms = rooms_;
}
string Hotel::getCity()
{
    return city;
}
void Hotel::setPrices(double standard, double deluxe, double luxury, double premium)
{
    prices[STANDARD_TYPE] = standard;
    prices[DELUXE_TYPE] = deluxe;
    prices[LUXURY_TYPE] = luxury;
    prices[PREMIUM_TYPE] = premium;
}
void Hotel::printBriefInfo()
{
    cout << uniqueId << SPACE << propertyName << SPACE << starRating << SPACE << city << SPACE << rooms.size();
    cout << SPACE << fixed << setprecision(2) << getAveragePrice()<<SPACE<< endl; 
}
double Hotel::getAveragePrice()
{
    int count = 0;
    double sum = 0;
    for (auto const &cost : prices)
    {
        if (cost.second != 0)
        {
            count++;
            sum += cost.second;
        }
    }
    if (count == 0)
        return 0;
    else
        return sum / count;
}
string Hotel::getUniqueId()
{
    return uniqueId;
}
void Hotel::printExtensiveInfo()
{
    cout << uniqueId << endl
         << propertyName << endl
         << STAR<<COLON<<SPACE << starRating << endl
         << OVERVIEW<<COLON<<SPACE << overview << endl
         << AMENITIES<<COLON<<SPACE << propertyAmenities << endl
         << CITY<<COLON<<SPACE << city << endl
         << LATITUDE<<COLON<<SPACE << fixed << setprecision(2) << latitude << endl
         << LONGITUDE<<COLON<<SPACE << fixed << setprecision(2) << longitude << endl
         << ROOMS<<COLON<<SPACE << getRoomsOfType(STANDARD_TYPE).size() << SPACE << getRoomsOfType(DELUXE_TYPE).size() << SPACE
         << getRoomsOfType(LUXURY_TYPE).size() << SPACE << getRoomsOfType(PREMIUM_TYPE).size() << endl
         << PRICE<<COLON<<SPACE << fixed << setprecision(0) << prices[STANDARD_TYPE] << SPACE << prices[DELUXE_TYPE] << SPACE
         << prices[LUXURY_TYPE] << SPACE << prices[PREMIUM_TYPE] << endl;
}
int Hotel::getStarRating()
{
    return starRating;
}
map<string, double> Hotel::getPrices()
{
    return prices;
}
vector<Room *> Hotel::getAvailableRooms(std::string type, Duration duration)
{
    vector<Room *> availableRooms;
    for (auto room : getRoomsOfType(type))
    {
        if (!room->isReservedIn(duration))
            availableRooms.push_back(room);
    }
    return availableRooms;
}
void Hotel::printReservedRooms(const vector<Room *> &bookedRooms)
{
    for (int i = 0; i < bookedRooms.size(); i++)
    {
        if (i != bookedRooms.size() - 1)
            cout << bookedRooms[i]->getId() << SPACE;
        else
            cout << bookedRooms[i]->getId() << endl;
    }
}
void Hotel::bookRooms(const vector<Room *> &availableRooms, Duration duration)
{
    for (auto room : availableRooms)
    {
        room->addReservation(duration);
    }
    printReservedRooms(availableRooms);
}
void Hotel::deleteReservation(string type, const vector<Room *> &reservedRooms, Duration duration)
{
    for (auto room : getRoomsOfType(type))
    {
        for (auto reserved : reservedRooms)
        {
            if (room->getId() == reserved->getId())
                room->cancelBooking(duration);
        }
    }
}
void Hotel::addComment(string username, string text)
{
    comments.push_back(Comment(username, text));
}
void Hotel::printComments()
{
    for (int i = comments.size() - 1; i >= 0; i--)
    {
        cout << comments[i].userName << COLON<<SPACE << comments[i].text << endl;
    }
}
void Hotel::addRating(Rating rating, string username)
{
    ratings[username] = rating;
}
Rating Hotel::getAverageRating()
{
    double cleanliness = 0, facilities = 0, location = 0, overallRating = 0, staff = 0, valueForMoney = 0;
    for (auto rating : ratings)
    {
        cleanliness += rating.second.cleanliness;
        facilities += rating.second.facilities;
        location += rating.second.location;
        overallRating += rating.second.overallRating;
        staff += rating.second.staff;
        valueForMoney += rating.second.valueForMoney;
    }
    return Rating(location / ratings.size(), cleanliness / ratings.size(), staff / ratings.size(),
                  facilities / ratings.size(), valueForMoney / ratings.size(), overallRating / ratings.size());
}
void Hotel::printAverageRating()
{
    if (ratings.size() == 0)
    {
        cout << NO_RATING;
        return;
    }
    Rating rating = getAverageRating();
    cout << fixed << setprecision(2) << LOCATION<<COLON<<SPACE << rating.location << endl
         << CLEANLINESS<<COLON<<SPACE << rating.cleanliness << endl
         << STAFF<<COLON<<SPACE << rating.staff << endl
         << FACILITIES<<COLON<<SPACE << rating.facilities << endl
         << VALUE_FOR_MONEY_PHRASE<<COLON<<SPACE << rating.valueForMoney << endl
         << OVERALL_RATING_PHRASE<<COLON<<SPACE << rating.overallRating << endl;
}
vector<Room *> Hotel::getRoomsOfType(string type)
{
    vector<Room *> specificRooms;
    for (auto room : rooms)
    {
        if (room->getType() == type)
            specificRooms.push_back(room);
    }
    return specificRooms;
}