#ifndef _HOTEL_H_
#define _HOTEL_H_ "_HOTEL_H_"

#include <vector>
#include <string>
#include <map>
#include "Room.hpp"
#include "StructsAndDefines.hpp"

class User;
class Hotel
{
private:
    std::string uniqueId;
    std::string propertyName;
    int starRating;
    std::string overview;
    std::string propertyAmenities;
    std::string city;
    double latitude;
    double longitude;
    std::string imageUrl;
    std::map<std::string, double> prices;
    std::vector<Room *> rooms;

public:
    Hotel(std::string uniqueId_, std::string propertyName_, int starRating_, std::string overview_, std::string propertyAmenities_, std::string city_,
          double latitude_, double logitude_, std::string imageUrl_, std::vector<Room *> rooms_);
    std::string getPropertyName();
    std::vector<Room*> getRoomsOfType(std::string type);
    std::map<std::string, double> getPrices();
    void setPrices(double standard, double deluxe, double luxury, double premium);
    std::string getUniqueId();
    std::string getCity();
    std::string getOverview();
    int getStarRating();
    std::string getImageUrl();
    std::vector <std::string> getAmenities();
};

#endif