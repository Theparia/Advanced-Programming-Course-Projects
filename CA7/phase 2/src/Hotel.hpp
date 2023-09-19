#ifndef _HOTEL_H_
#define _HOTEL_H_ "_HOTEL_H_"

#include <vector>
#include <string>
#include <map>
#include "Room.hpp"
#include "StructsAndDefines.hpp"
#include "Rating.hpp"

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
    std::vector<Comment> comments;
    std::map <std::string,Rating> ratings;

public:
    Hotel(std::string uniqueId_, std::string propertyName_, int starRating_, std::string overview_, std::string propertyAmenities_, std::string city_,
          double latitude_, double logitude_, std::string imageUrl_, std::vector<Room *> rooms_);
    double getAveragePrice();
    std::string getPropertyName();
    std::vector<Room*> getRoomsOfType(std::string type);
    std::map<std::string, double> getPrices();
    void setPrices(double standard, double deluxe, double luxury, double premium);
    void printBriefInfo();
    void printExtensiveInfo();
    std::string getUniqueId();
    std::string getCity();
    int getStarRating();
    std::vector<Room *> getAvailableRooms(std::string type, Duration duration);
    void bookRooms(const std::vector<Room *> &bookedRooms, Duration duration);
    void deleteReservation(std::string type, const std::vector<Room *> &rooms, Duration duration);
    void addComment(std::string username, std::string text);
    void printComments();
    void addRating(Rating rating,std::string username);
    Rating getAverageRating();
    void printAverageRating();
    void printReservedRooms(const std::vector<Room *> &bookedRooms);
    std::map <std::string,Rating> getRatings();
    bool hasPostRatingBefore(User* user);
    double getPersonalRating(User* user,Rating estimatedWeights);
};

#endif