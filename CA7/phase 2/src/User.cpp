#include "User.hpp"
#include "Exception.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <random>

using namespace std;

User::User(std::string email_, std::string userName_, size_t passWord_)
{
    email = email_;
    userName = userName_;
    passWord = passWord_;
    wallet.accountBalance = ZERO;
    wallet.turnover.push_back(ZERO);
    newReservationId = 1;
    isDefaultPriceFilterOn = true;
    areManualWeightsActive = false;
}

string User::getUserName()
{
    return userName;
}
string User::getEmail()
{
    return email;
}
size_t User::getPassword()
{
    return passWord;
}
void User::chargeAccount(double amount)
{
    if (amount <= ZERO)
        throw BadRequestException();
    wallet.accountBalance += amount;
    wallet.turnover.push_back(wallet.accountBalance);
}
double User::getAccountBalance()
{
    return wallet.accountBalance;
}
void User::printTurnover(int count)
{
    if (count > wallet.turnover.size())
        count = wallet.turnover.size();
    for (int i = 1; i <= count; i++)
    {
        cout << fixed << setprecision(0) << wallet.turnover[wallet.turnover.size() - i] << endl;
    }
}
void User::deleteFilters()
{
    filters.clear();
}
vector<Hotel *> User::applyFilters(const vector<Hotel *> &hotels)
{
    vector<Hotel *> filteredHotels = hotels;
    addDefaultPriceFilter();
    for (auto filter : filters)
    {
        filteredHotels = filter.second->applyFilter(filteredHotels);
    }
    deleteDefaultPriceFilter();
    return filteredHotels;
}
void User::addDefaultPriceFilter()
{
    if (isDefaultPriceFilterActive())
    {
        DefaultPriceFilter *filter = new DefaultPriceFilter(getSampleAverage(), getStandardDeviation());
        filters[DefaultPrice] = filter;
    }
}
void User::deleteDefaultPriceFilter()
{
    if (filters.find(DefaultPrice) != filters.end())
        filters.erase(filters.find(DefaultPrice));
}
void User::payReservation(double price)
{
    if (price > wallet.accountBalance)
        throw NotEnoughCreditException();
    wallet.accountBalance -= price;
    wallet.turnover.push_back(wallet.accountBalance);
}
void User::addReservation(Hotel *hotel, std::string type, Duration durationOfStay, std::vector<Room *> rooms)
{
    Reservation *reserve = new Reservation(newReservationId, hotel, type, durationOfStay, rooms);
    payReservation(reserve->getTotalPrice());
    newReservationId++;
    reservations.push_back(reserve);
}
Reservation *User::findReservationById(int id)
{
    for (auto reservation : reservations)
    {
        if (reservation->getId() == id)
            return reservation;
    }
    throw NonExistenseException();
}
void User::deleteReservation(int id)
{
    Reservation *reserve = findReservationById(id);
    chargeAccount(reserve->getTotalPrice() / TWO);
    reserve->cancel();
    reservations.erase(find(reservations.begin(), reservations.end(), reserve));
}
void User::printReservationsInfo()
{
    sort(reservations.begin(), reservations.end(), compareReservationId);
    if (reservations.size() == 0)
        cout << EMPTY;
    else
        for (auto reservation : reservations)
            reservation->printInfo();
}
bool User::compareReservationId(Reservation *r1, Reservation *r2)
{
    return r1->getId() > r2->getId();
}
void User::addFilter(Filter *newFilter, filterType type)
{
    filters[type] = newFilter;
}
void User::changeDefaultPriceActivation(bool state)
{
    isDefaultPriceFilterOn = state;
}
double User::getSampleAverage()
{
    double sum = accumulate(reservations.begin(), reservations.end(), 0, [](double acc, Reservation *reserve) { return acc + reserve->getRoomsPrices(); });
    int count = accumulate(reservations.begin(), reservations.end(), 0, [](double acc, Reservation *reserve) { return acc + reserve->getQuantity(); });
    return sum / count;
}
double User::getStandardDeviation()
{
    double average = getSampleAverage();
    double sum, count;
    vector<double> result(reservations.size(), average);
    transform(reservations.begin(), reservations.end(), result.begin(), result.begin(), [](Reservation *res, double avg) { return res->getQuantity() * pow(res->getSingleRoomPrice() - avg, 2); });
    sum = accumulate(result.begin(), result.end(), 0);
    count = accumulate(reservations.begin(), reservations.end(), 0, [](double acc, Reservation *reserve) { return acc + reserve->getQuantity(); });
    return sqrt(sum / (count - 1));
}
bool User::isDefaultPriceFilterActive()
{
    return isDefaultPriceFilterOn && reservations.size() >= TEN && filters.find(AveragePrice) == filters.end();
}
void User::setManualWeights(Rating manualWeights_)
{
    manualWeights = manualWeights_;
    areManualWeightsActive = true;
}
void User::printManualWeights()
{
    if (areManualWeightsActive)
    {
        manualWeights.printManualWeights();
    }
    else
        cout << ACTIVE << SPACE << FALSE_STATE << endl;
}
void User::turnManualWeightsOff()
{
    areManualWeightsActive = false;
}
bool User::areManualWeightsOn()
{
    return areManualWeightsActive;
}
Rating User::getManualWeights()
{
    return manualWeights;
}
void User::addRating(string hotelId, Rating rating)
{
    ratings[hotelId] = rating;
}
map<string, Rating> User::getRatings()
{
    return ratings;
}
Rating User::getEstimatedWeights()
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(1.0, 5.0);
    Rating estimatedWeight(distribution(generator), distribution(generator), distribution(generator), distribution(generator), distribution(generator), distribution(generator));
    vector<double> deltas;
    for (int i = 0; i < 1000; i++)
    {
        deltas = estimatedWeight.getDeltas(ratings);
        estimatedWeight -= deltas;
        estimatedWeight.clampAllElements();
    }
    return estimatedWeight;
}
