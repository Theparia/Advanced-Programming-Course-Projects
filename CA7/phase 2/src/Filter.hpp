#ifndef _FILTER_H_
#define _FILTER_H_ "_FILTER_H_"

#include "Hotel.hpp"
#include "Reservation.hpp"
#include <vector>
#include <string>

class Filter
{
public:
    virtual std::vector<Hotel *> applyFilter(std::vector<Hotel *> hotels) = 0;
};

class CityFilter : public Filter
{
private:
    std::string city;

public:
    CityFilter(std::string city_);
    std::vector<Hotel *> applyFilter(std::vector<Hotel *> hotels);
};

class StarRatingFilter : public Filter
{
private:
    int minStar;
    int maxStar;

public:
    StarRatingFilter(int minStar_, int maxStar_);
    std::vector<Hotel *> applyFilter(std::vector<Hotel *> hotels);
    bool isInvalid();
};

class AveragePriceFilter : public Filter
{
private:
    double minPrice;
    double maxPrice;

public:
    AveragePriceFilter(double minPrice_, double maxPrice_);
    std::vector<Hotel *> applyFilter(std::vector<Hotel *> hotels);
    bool isInvalid();
};

class SpecialRoomsFilter : public Filter
{
private:
    std::string roomType;
    int quantity;
    Duration durationOfStay;

public:
    SpecialRoomsFilter(std::string roomType_, int quantity_, Duration durationOfStay_);
    std::vector<Hotel *> applyFilter(std::vector<Hotel *> hotels);
    bool isInvalid();
};
class DefaultPriceFilter : public Filter
{
private:
    double sampleAverage;
    double standardDeviation;

public:
    DefaultPriceFilter(double sampleAverage_, double standardDeviation_);
    std::vector<Hotel *> applyFilter(std::vector<Hotel *> hotels);
};

#endif