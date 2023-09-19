#ifndef _UTRIP_H_
#define _UTRIP_H_ "_UTRIP_H_"

#include "Hotel.hpp"
#include "User.hpp"
#include <vector>
#include <string>
#include "CSVReader.hpp"

class Utrip
{
private:
    CSVReader csvReader;
    std::vector<User *> users;
    std::vector<Hotel *> hotels;
    bool isSomeoneLoggedIn;
    User *currentUser;
    bool areTheHotelsViewable;

public:
    Utrip(std::string hotelsFilePath, std::string ratingsFilePath);
    size_t hashPassword(std::string password);
    void signUpUser(std::string email, std::string username, std::string password);
    bool isSignUpInvalid(std::string email, std::string username);
    User *findUserByEmail(std::string email, std::string password);
    void logOut();
    void logIn(std::string email, std::string password);
    void chargeWallet(double amount);
    void printTurnover(int count);
    void printHotelsInfo();
    void printSpecifiedHotelInfo(std::string id);
    Hotel *findHotelById(std::string id);
    void bookRooms(std::string hotelId, std::string roomType, int quantity, Duration durationOfStay);
    void deleteReservation(int id);
    void getReserves();
    void addCityFilter(std::string city);
    void addStarRatingFilter(int minStar, int maxStar);
    void addAveragePriceFilter(double minPrice, double maxPrice);
    void addSpecialRoomsFilter(std::string type, int quantity, Duration durationOfStay);
    void deleteFilters();
    void addComment(std::string hotelId, std::string text);
    void printComments(std::string hotelId);
    void addRating(std::string hotelId, Rating rating);
    void printAverageRating(std::string hotelId);
    bool isThereEnoughRoom(const std::vector<Room *> &availableRooms, int quantity);
    std::vector<Room *> getBookedRooms(const std::vector<Room *> &availableRooms, int quantity);
    bool isLoggedIn();
    void sortHotels(std::string property, std::string order);
    void sortByCity(std::string order);
    void sortById(std::string order);
    void sortByName(std::string order);
    void sortByStarRating(std::string order);
    void sortByAveragePrice(std::string order);
    void sortByRoomPrice(std::string type, std::string order);
    void sortByPersonalRating(std::string order);
    void changeDefaultPriceActivation(std::string state);
    void setAverageRatings(std::map<std::string, Rating> averageRatings);
    void addManualWeights(Rating manualWeights);
    void turnManualWeightsOff();
    User *getCurrentUser();
    void getEstimatedWeights();
};

#endif