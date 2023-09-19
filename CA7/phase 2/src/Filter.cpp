#include "Filter.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

using namespace std;

CityFilter::CityFilter(string city_)
{
    city = city_;
}
vector<Hotel *> CityFilter::applyFilter(vector<Hotel *> hotels)
{
    vector<Hotel *> filteredHotels;
    for (auto hotel : hotels)
    {
        if (hotel->getCity() == city)
            filteredHotels.push_back(hotel);
    }
    return filteredHotels;
}
StarRatingFilter::StarRatingFilter(int minStar_, int maxStar_)
{
    minStar = minStar_;
    maxStar = maxStar_;
}
vector<Hotel *> StarRatingFilter::applyFilter(vector<Hotel *> hotels)
{
    vector<Hotel *> filteredHotels;
    for (auto hotel : hotels)
    {
        if (hotel->getStarRating() >= minStar && hotel->getStarRating() <= maxStar)
            filteredHotels.push_back(hotel);
    }
    return filteredHotels;
}
bool StarRatingFilter::isInvalid()
{
    return minStar < ONE || minStar > FIVE || maxStar < ONE || maxStar > FIVE || minStar > maxStar;
}

AveragePriceFilter::AveragePriceFilter(double minPrice_, double maxPrice_)
{
    minPrice = minPrice_;
    maxPrice = maxPrice_;
}
vector<Hotel *> AveragePriceFilter::applyFilter(vector<Hotel *> hotels)
{
    vector<Hotel *> filteredHotels;
    for (auto hotel : hotels)
    {
        if (hotel->getAveragePrice() >= minPrice && hotel->getAveragePrice() <= maxPrice)
            filteredHotels.push_back(hotel);
    }
    return filteredHotels;
}
bool AveragePriceFilter::isInvalid()
{
    return minPrice < ZERO || maxPrice < ZERO || minPrice > maxPrice;
}
SpecialRoomsFilter::SpecialRoomsFilter(std::string roomType_, int quantity_, Duration durationOfStay_)
{
    roomType = roomType_;
    quantity = quantity_;
    durationOfStay = durationOfStay_;
}
vector<Hotel *> SpecialRoomsFilter::applyFilter(vector<Hotel *> hotels)
{
    vector<Hotel *> filteredHotels;
    for (auto hotel : hotels)
    {
        vector<Room *> availableRooms = hotel->getAvailableRooms(roomType, durationOfStay);
        if (availableRooms.size() >= quantity)
            filteredHotels.push_back(hotel);
    }
    return filteredHotels;
}
bool SpecialRoomsFilter::isInvalid()
{
    return durationOfStay.checkIn > durationOfStay.checkOut;
}
DefaultPriceFilter::DefaultPriceFilter(double sampleAverage_, double standardDeviation_)
{
    sampleAverage = sampleAverage_;
    standardDeviation = standardDeviation_;
}
vector<Hotel *> DefaultPriceFilter::applyFilter(vector<Hotel *> hotels)
{
    vector<Hotel *> filteredHotels;
    cout << DEFAULT_PRICE_FILTER_PHRASE;
    for (auto hotel : hotels)
    {
        if (abs(hotel->getAveragePrice() - sampleAverage) <= (2 * standardDeviation))
            filteredHotels.push_back(hotel);
    }
    return filteredHotels;
}