#include "User.hpp"
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
    wallet.accountBalance += amount;
    wallet.turnover.push_back(wallet.accountBalance);
}
double User::getAccountBalance()
{
    return wallet.accountBalance;
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
void User::addFilter(Filter *newFilter, filterType type)
{
    filters[type] = newFilter;
}
