#include "Hotel.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "User.hpp"
#include <numeric>

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
string Hotel::getPropertyName()
{
    return propertyName;
}
string Hotel::getUniqueId()
{
    return uniqueId;
}
int Hotel::getStarRating()
{
    return starRating;
}
map<string, double> Hotel::getPrices()
{
    return prices;
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
string Hotel::getImageUrl()
{
    return imageUrl;
}
string Hotel::getOverview()
{
    return overview;
}
vector <string> Hotel::getAmenities()
{
    string line;
    vector<string> amenities;
    stringstream file(propertyAmenities);
    while (getline(file, line,'|'))
    {
        amenities.push_back(line);
    }
    return amenities;
}