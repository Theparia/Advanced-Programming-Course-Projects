#include "User.hpp"
#include "Exception.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

User::User(std::string email_, std::string userName_, size_t passWord_)
{
    email = email_;
    userName = userName_;
    passWord = passWord_;
    wallet.accountBalance = ZERO;
    wallet.turnover.push_back(ZERO);
    newReservationId = 1;
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
    for (auto filter : filters)
    {
        filteredHotels = filter.second->applyFilter(filteredHotels);
    }
    return filteredHotels;
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
void User::addFilter(Filter *newFilter,filterType type)
{
    filters[type]=newFilter;
}