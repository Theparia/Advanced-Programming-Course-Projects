#ifndef _USER_H_
#define _USER_H_ "_USER_H_"

#include <vector>
#include <string>
#include <map>
#include "Filter.hpp"
#include "Hotel.hpp"

class User
{
private:
    std::string email;
    std::string userName;
    size_t passWord;
    Wallet wallet;
    std::map<filterType, Filter *> filters;

public:
    User(std::string email_, std::string userName_, size_t passWord_);
    std::string getUserName();
    std::string getEmail();
    size_t getPassword();
    void chargeAccount(double amount);
    double getAccountBalance();
    void deleteFilters();
    std::vector<Hotel *> applyFilters(const std::vector<Hotel *> &hotels);
    virtual void addFilter(Filter *filter, filterType type);
};

#endif