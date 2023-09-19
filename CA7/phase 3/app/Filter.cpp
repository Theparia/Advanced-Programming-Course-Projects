#include "Filter.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

using namespace std;


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

