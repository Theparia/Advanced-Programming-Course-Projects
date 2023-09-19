#include "Utrip.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "Exception.hpp"
#include <functional>
#include <iomanip>

using namespace std;

Utrip::Utrip(string hotelsFilePath, string ratingsFilePath)
{
    hotels = csvReader.readHotelsData(hotelsFilePath);
    setAverageRatings(csvReader.readRatingsData(ratingsFilePath));
    sortById(ASCENDING_ORDER);
    isSomeoneLoggedIn = false;
    currentUser = NULL;
    areTheHotelsViewable = true;
}
bool Utrip::isLoggedIn()
{
    return isSomeoneLoggedIn;
}
User *Utrip::getCurrentUser()
{
    return currentUser;
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
    currentUser->changeDefaultPriceActivation(true);
    currentUser->turnManualWeightsOff();
    currentUser = NULL;
    isSomeoneLoggedIn = false;
    sortById(ASCENDING_ORDER);
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
void Utrip::printHotelsInfo()
{
    if (!areTheHotelsViewable)
        throw InsufficientRatingsException();
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
void Utrip::addRating(std::string hotelId, Rating rating)
{
    Hotel *hotel = findHotelById(hotelId);
    if (rating.isInvalid())
        throw BadRequestException();
    hotel->addRating(rating, currentUser->getUserName());
    currentUser->addRating(hotelId, rating);
    cout << OK;
}
void Utrip::addManualWeights(Rating manualWeights)
{
    if (manualWeights.isInvalid())
        throw BadRequestException();
    currentUser->setManualWeights(manualWeights);
    cout << OK;
}
void Utrip::turnManualWeightsOff()
{
    currentUser->turnManualWeightsOff();
    cout << OK;
}
void Utrip::printAverageRating(string hotelId)
{
    Hotel *hotel = findHotelById(hotelId);
    hotel->printAverageRating();
}
void Utrip::sortHotels(string property, string order)
{
    if (order != ASCENDING_ORDER && order != DESCENDING_ORDER)
        throw BadRequestException();
    if (property == ID)
        sortById(order);
    else if (property == HOTEL_NAME)
        sortByName(order);
    else if (property == STAR_RATING)
        sortByStarRating(order);
    else if (property == CITY)
        sortByCity(order);
    else if (property == STANDARD_ROOM_PRICE || property == DELUXE_ROOM_PRICE || property == LUXURY_ROOM_PRICE || property == PREMIUM_ROOM_PRICE)
        sortByRoomPrice(csvReader.parseData(property, '_')[0], order);
    else if (property == AVERAGE_ROOM_PRICE)
        sortByAveragePrice(order);
    else if (property == PERSONAL_RATING)
        sortByPersonalRating(order);
    else
        throw BadRequestException();
    cout << OK;
}
void Utrip::sortById(string order)
{
    areTheHotelsViewable = true;
    sort(hotels.begin(), hotels.end(), [order](Hotel *first, Hotel *second) {
        if(order==ASCENDING_ORDER)
            return first->getUniqueId() < second->getUniqueId();
        if(order==DESCENDING_ORDER)
            return first->getUniqueId() > second->getUniqueId(); });
}
void Utrip::sortByRoomPrice(string type, string order)
{
    areTheHotelsViewable = true;
    sort(hotels.begin(), hotels.end(), [type, order](Hotel *first, Hotel *second) {
        if (first->getPrices()[type] == second->getPrices()[type])
            return first->getUniqueId() < second->getUniqueId();
        if(order==DESCENDING_ORDER)
            return first->getPrices()[type] > second->getPrices()[type];
        if(order==ASCENDING_ORDER)
            return first->getPrices()[type] < second->getPrices()[type]; });
}
void Utrip::sortByCity(string order)
{
    areTheHotelsViewable = true;
    sort(hotels.begin(), hotels.end(), [order](Hotel *first, Hotel *second) {
        if (first->getCity() == second->getCity())
            return first->getUniqueId() < second->getUniqueId();
        if(order==ASCENDING_ORDER)
            return first->getCity() < second->getCity();
        if(order==DESCENDING_ORDER)
            return first->getCity() > second->getCity(); });
}
void Utrip::sortByName(string order)
{
    areTheHotelsViewable = true;
    sort(hotels.begin(), hotels.end(), [order](Hotel *first, Hotel *second) {
        if(first->getPropertyName()==second->getPropertyName())
            return first->getUniqueId() < second->getUniqueId();
        if(order==ASCENDING_ORDER)
            return first->getPropertyName() < second->getPropertyName();
        if(order==DESCENDING_ORDER)
            return first->getPropertyName() > second->getPropertyName(); });
}
void Utrip::sortByStarRating(string order)
{
    areTheHotelsViewable = true;
    sort(hotels.begin(), hotels.end(), [order](Hotel *first, Hotel *second) {
        if (first->getStarRating() == second->getStarRating())
            return first->getUniqueId() < second->getUniqueId();
        if(order==ASCENDING_ORDER)
            return first->getStarRating() < second->getStarRating(); 
        if(order==DESCENDING_ORDER)
            return first->getStarRating() > second->getStarRating(); });
}

void Utrip::sortByAveragePrice(string order)
{
    areTheHotelsViewable = true;
    sort(hotels.begin(), hotels.end(), [order](Hotel *first, Hotel *second) {
        if (first->getAveragePrice() == second->getAveragePrice())
            return first->getUniqueId() < second->getUniqueId();
        if(order==ASCENDING_ORDER)   
            return first->getAveragePrice() < second->getAveragePrice();
        if(order==DESCENDING_ORDER)
            return first->getAveragePrice() > second->getAveragePrice(); });
}
void Utrip::sortByPersonalRating(string order)
{
    Rating estimatedWeights = currentUser->getEstimatedWeights();
    if (!currentUser->areManualWeightsOn() && currentUser->getRatings().size() < FIVE)
    {
        areTheHotelsViewable = false;
        return;
    }
    areTheHotelsViewable = true;
    sort(hotels.begin(), hotels.end(), [order, this, estimatedWeights](Hotel *first, Hotel *second) {
        if (first->getPersonalRating(currentUser,estimatedWeights) == second->getPersonalRating(currentUser,estimatedWeights))
            return first->getUniqueId() < second->getUniqueId();
        if(order==ASCENDING_ORDER)   
            return first->getPersonalRating(currentUser,estimatedWeights) < second->getPersonalRating(currentUser,estimatedWeights);
        if(order==DESCENDING_ORDER)
            return first->getPersonalRating(currentUser,estimatedWeights) > second->getPersonalRating(currentUser,estimatedWeights); });
}
void Utrip::changeDefaultPriceActivation(string state)
{
    if (state == TRUE_STATE)
        currentUser->changeDefaultPriceActivation(true);
    else if (state == FALSE_STATE)
        currentUser->changeDefaultPriceActivation(false);
    else
        throw BadRequestException();
    cout << OK;
}
void Utrip::setAverageRatings(map<string, Rating> averageRatings)
{
    for (auto rating : averageRatings)
    {
        findHotelById(rating.first)->addRating(rating.second, RATINGS_FILE);
    }
}
void Utrip::getEstimatedWeights()
{
    if (currentUser->getRatings().size() < FIVE)
        throw InsufficientRatingsException();
    Rating weights = currentUser->getEstimatedWeights();
    weights.printEstimatedWeights();
}