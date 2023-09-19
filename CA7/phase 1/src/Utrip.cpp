#include "Utrip.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "Exception.hpp"
#include <functional>

using namespace std;

Utrip::Utrip(string filePath)
{
    hotels=csvReader.readHotelsData(filePath);
    sort(hotels.begin(), hotels.end(), compareId);
    isSomeoneLoggedIn = false;
    currentUser = NULL;
}
bool Utrip:: isLoggedIn()
{
    return isSomeoneLoggedIn;
}
size_t Utrip::hashPassword(string password)
{
    size_t passwordHash = hash<string>{}(password);
    return passwordHash;
}
void Utrip::signUpUser(string email, string username, string password)
{
    if (isSignUpInvalid(email, username) || isSomeoneLoggedIn)
        throw BadRequestException();
    User *user = new User(email, username, hashPassword(password));
    users.push_back(user);
    isSomeoneLoggedIn = true;
    currentUser = user;
    cout << OK;
}
bool Utrip::isSignUpInvalid(string email, string username)
{
    for (auto user : users)
    {
        if (user->getEmail() == email || user->getUserName() == username)
            return true;
    }
    return false;
}
void Utrip::logOut()
{
    currentUser->deleteFilters();
    currentUser = NULL;
    isSomeoneLoggedIn = false;
    cout << OK;
}
User *Utrip::findUserByEmail(string email, string password)
{
    for (auto user : users)
    {
        if (user->getEmail() == email && user->getPassword() == hashPassword(password))
            return user;
    }
    throw BadRequestException();
}

void Utrip::logIn(string email, string password)
{
    if (isSomeoneLoggedIn)
        throw BadRequestException();
    currentUser = findUserByEmail(email, password);
    isSomeoneLoggedIn = true;
    cout << OK;
}
void Utrip::chargeWallet(double amount)
{
    currentUser->chargeAccount(amount);
    cout << OK;
}

void Utrip::printTurnover(int count)
{
    currentUser->printTurnover(count);
}
bool Utrip::compareId(Hotel *h1, Hotel *h2)
{
    return h1->getUniqueId() < h2->getUniqueId();
}
void Utrip::printHotelsInfo()
{
    vector<Hotel *> filterd = currentUser->applyFilters(hotels);
    if (filterd.size() == ZERO)
        cout << EMPTY;
    else
        for (auto filter : filterd)
            filter->printBriefInfo();
}
Hotel *Utrip::findHotelById(string id)
{
    for (auto hotel : hotels)
    {
        if (hotel->getUniqueId() == id)
            return hotel;
    }
    throw NonExistenseException();
}
void Utrip::printSpecifiedHotelInfo(string id)
{
    findHotelById(id)->printExtensiveInfo();
}
bool Utrip::isThereEnoughRoom(const vector<Room *> &availableRooms, int quantity)
{
    return quantity <= availableRooms.size();
}
vector<Room *> Utrip::getBookedRooms(const vector<Room *> &availableRooms, int quantity)
{
    vector<Room *> booked;
    for (int i = 0; i < quantity; i++)
    {
        booked.push_back(availableRooms[i]);
    }
    return booked;
}
void Utrip::bookRooms(string hotelId, string roomType, int quantity, Duration durationOfStay)
{
    Hotel *hotel = findHotelById(hotelId);
    vector<Room *> availableRooms = hotel->getAvailableRooms(roomType, durationOfStay);
    if (!isThereEnoughRoom(availableRooms, quantity))
        throw NotEnoughRoomException();
    currentUser->addReservation(hotel, roomType, durationOfStay, getBookedRooms(availableRooms, quantity));
    hotel->bookRooms(getBookedRooms(availableRooms, quantity), durationOfStay);
}
void Utrip::deleteReservation(int id)
{
    currentUser->deleteReservation(id);
    cout << OK;
}
void Utrip::getReserves()
{
    currentUser->printReservationsInfo();
}
void Utrip::addCityFilter(string city)
{
    CityFilter *filter = new CityFilter(city);
    currentUser->addFilter(filter, City);
    cout << OK;
}
void Utrip::addStarRatingFilter(int minStar, int maxStar)
{
    StarRatingFilter *filter = new StarRatingFilter(minStar, maxStar);
    if (filter->isInvalid())
        throw BadRequestException();
    currentUser->addFilter(filter, StarRating);
    cout << OK;
}
void Utrip::addAveragePriceFilter(double minPrice, double maxPrice)
{
    AveragePriceFilter *filter = new AveragePriceFilter(minPrice, maxPrice);
    if (filter->isInvalid())
        throw BadRequestException();
    currentUser->addFilter(filter, AveragePrice);
    cout << OK;
}
void Utrip::addSpecialRoomsFilter(string type, int quantity, Duration durationOfStay)
{
    SpecialRoomsFilter *filter = new SpecialRoomsFilter(type, quantity, durationOfStay);
    if (filter->isInvalid())
        throw BadRequestException();
    currentUser->addFilter(filter, DurationOfStay);
    cout << OK;
}
void Utrip::deleteFilters()
{
    currentUser->deleteFilters();
    cout << OK;
}
void Utrip::addComment(string hotelId, string text)
{
    Hotel *hotel = findHotelById(hotelId);
    hotel->addComment(currentUser->getUserName(), text);
    cout << OK;
}
void Utrip::printComments(std::string hotelId)
{
    Hotel *hotel = findHotelById(hotelId);
    hotel->printComments();
}
bool Utrip::isRatingInvalid(Rating rating)
{
    return rating.cleanliness < ONE || rating.cleanliness > FIVE || rating.facilities < ONE || rating.facilities > FIVE || rating.location < ONE|| rating.location > FIVE ||
        rating.overallRating < ONE || rating.overallRating > FIVE || rating.staff < ONE || rating.staff > FIVE || rating.valueForMoney < ONE || rating.valueForMoney > FIVE;
}
void Utrip::addRating(std::string hotelId, Rating rating)
{
    Hotel *hotel = findHotelById(hotelId);
    if (isRatingInvalid(rating))
        throw BadRequestException();
    hotel->addRating(rating, currentUser->getUserName());
    cout << OK;
}
void Utrip::printAverageRating(string hotelId)
{
    Hotel *hotel = findHotelById(hotelId);
    hotel->printAverageRating();
}