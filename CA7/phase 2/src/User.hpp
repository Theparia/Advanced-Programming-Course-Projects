#ifndef _USER_H_
#define _USER_H_ "_USER_H_"

#include <vector>
#include <string>
#include <map>
#include "Filter.hpp"
#include "Hotel.hpp"
#include "Reservation.hpp"

class User
{
private:
    std::string email;
    std::string userName;
    size_t passWord;
    Wallet wallet;
    int newReservationId;
    std::vector<Reservation *> reservations;
    std::map<filterType, Filter *> filters;
    std::map<std::string, Rating> ratings;
    bool isDefaultPriceFilterOn;
    bool areManualWeightsActive;
    Rating manualWeights;

public:
    User(std::string email_, std::string userName_, size_t passWord_);
    std::string getUserName();
    std::string getEmail();
    size_t getPassword();
    void chargeAccount(double amount);
    double getAccountBalance();
    void printTurnover(int count);
    void deleteFilters();
    std::vector<Hotel *> applyFilters(const std::vector<Hotel *> &hotels);
    void addReservation(Hotel *hotel, std::string type, Duration durationOfStay, std::vector<Room *> rooms);
    Reservation *findReservationById(int id);
    void payReservation(double price);
    void deleteReservation(int id);
    void printReservationsInfo();
    virtual void addFilter(Filter *filter, filterType type);
    static bool compareReservationId(Reservation *r1, Reservation *r2);
    double getSampleAverage();
    double getStandardDeviation();
    bool isDefaultPriceFilterActive();
    void addDefaultPriceFilter();
    void deleteDefaultPriceFilter();
    void changeDefaultPriceActivation(bool onOrOff);
    void setManualWeights(Rating manualWeights_);
    void printManualWeights();
    void turnManualWeightsOff();
    bool areManualWeightsOn();
    Rating getManualWeights();
    void addRating(std::string hotelId, Rating rating);
    std::map<std::string, Rating> getRatings();
    Rating getEstimatedWeights();
};

#endif