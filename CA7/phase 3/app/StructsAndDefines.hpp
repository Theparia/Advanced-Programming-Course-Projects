#ifndef _STRUCTS_AND_DEFINES_H_
#define _STRUCTS_AND_DEFINES_H_ "_STRUCTS_AND_DEFINES_H_"

#include <string>
#include <vector>

#define STANDARD_TYPE "standard"
#define DELUXE_TYPE "deluxe"
#define LUXURY_TYPE "luxury"
#define PREMIUM_TYPE "premium"
#define SPACE ' '
#define OK "OK\n"
#define ONE 1
#define FIVE 5
#define ZERO 0
#define NEW_LINE '\n'
#define COMMA ','

enum filterType
{
    City,
    StarRating,
    AveragePrice,
    DurationOfStay,
    DefaultPrice
};
struct Wallet
{
    double accountBalance;
    std::vector<double> turnover;
};

#endif