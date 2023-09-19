#include "Utrip.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <iomanip>
#include "../server/server.hpp"

using namespace std;

UtripService::UtripService(string hotelsFilePath)
{
    hotels = csvReader.readHotelsData(hotelsFilePath);
    sort(hotels.begin(), hotels.end(), [](Hotel *a, Hotel *b) { return a->getUniqueId() < b->getUniqueId(); });
}
vector<Hotel *> UtripService::getFilteredHotels(string id)
{
    return sessions[id]->applyFilters(hotels);
}
size_t UtripService::hashPassword(string password)
{
    size_t passwordHash = hash<string>{}(password);
    return passwordHash;
}
void UtripService::signUpUser(string email, string username, string password)
{
    User *user = new User(email, username, hashPassword(password));
    users.push_back(user);
    sessions[username] = user;
    cout << OK;
}
bool UtripService::isSignUpInvalid(string email, string username)
{
    for (auto user : users)
    {
        if (user->getEmail() == email || user->getUserName() == username)
            return true;
    }
    return false;
}
bool UtripService::isLoginValid(string username, string password)
{
    for (auto user : users)
    {
        if (user->getUserName() == username && user->getPassword() == hashPassword(password))
            return true;
    }
    return false;
}
void UtripService::logOut(string id)
{
    sessions[id]->deleteFilters();
    sessions.erase(id);
    cout << OK;
}
User *UtripService::findUserByUsername(string username, string password)
{
    for (auto user : users)
    {
        if (user->getUserName() == username && user->getPassword() == hashPassword(password))
            return user;
    }
}

void UtripService::logIn(string username, string password)
{
    User *user = findUserByUsername(username, password);
    sessions[username] = user;
    cout << OK;
}
void UtripService::chargeWallet(double amount, string id)
{
    sessions[id]->chargeAccount(amount);
    cout << OK;
}
double UtripService::getAccountBalance(string id)
{
    return sessions[id]->getAccountBalance();
}

Hotel *UtripService::findHotelById(string id)
{
    for (auto hotel : hotels)
    {
        if (hotel->getUniqueId() == id)
            return hotel;
    }
}

void UtripService::addStarRatingFilter(int minStar, int maxStar, string id)
{
    StarRatingFilter *filter = new StarRatingFilter(minStar, maxStar);
    sessions[id]->addFilter(filter, StarRating);
    cout << OK;
}
User *UtripService::getUserBySessionId(std::string id)
{
    return sessions[id];
}
bool UtripService::hasSomeOneLoggedIn()
{
    if (sessions.size() > 0)
        return true;
    return false;
}