#ifndef _FILTER_H_
#define _FILTER_H_ "_FILTER_H_"

#include "Hotel.hpp"
#include <vector>
#include <string>

class Filter
{
public:
    virtual std::vector<Hotel *> applyFilter(std::vector<Hotel *> hotels) = 0;
};

class StarRatingFilter : public Filter
{
private:
    int minStar;
    int maxStar;

public:
    StarRatingFilter(int minStar_, int maxStar_);
    std::vector<Hotel *> applyFilter(std::vector<Hotel *> hotels);
};


#endif