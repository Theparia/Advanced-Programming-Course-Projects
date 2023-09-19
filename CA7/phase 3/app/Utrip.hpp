#ifndef _UTRIP_H_
#define _UTRIP_H_ "_UTRIP_H_"

#include "Hotel.hpp"
#include "User.hpp"
#include <vector>
#include <string>
#include "CSVReader.hpp"
#include <map>

class UtripService
{
private:
    CSVReader csvReader;
    std::vector<User *> users;
    std::vector<Hotel *> hotels;
    std::map<std::string, User *> sessions;

public:
    UtripService(std::string hotelsFilePath);
    size_t hashPassword(std::string password);
    void signUpUser(std::string email, std::string username, std::string password);
    bool isSignUpInvalid(std::string email, std::string username);
    bool isLoginValid(std::string username,std::string password);
    User *findUserByUsername(std::string username, std::string password);
    void logOut(std::string id);
    void logIn(std::string username, std::string password);
    void chargeWallet(double amount,std::string id);
    double getAccountBalance(std::string id);
    Hotel *findHotelById(std::string id);
    void addStarRatingFilter(int minStar, int maxStar,std::string id);
    std::vector<Hotel *> getFilteredHotels(std::string id);
    User* getUserBySessionId(std::string id);
    bool hasSomeOneLoggedIn();
};

#endif