#include "Rating.hpp"
#include "StructsAndDefines.hpp"
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

Rating::Rating(double location_, double cleanliness_, double staff_, double facilities_, double valueForMoney_, double overallRating_)
{
    location = location_;
    cleanliness = cleanliness_;
    staff = staff_;
    facilities = facilities_;
    valueForMoney = valueForMoney_;
    overallRating = overallRating_;
}
Rating Rating::operator*(Rating rating)
{
    return Rating(location * rating.location, cleanliness * rating.cleanliness, staff * rating.staff, facilities * rating.facilities, valueForMoney * rating.valueForMoney, overallRating * rating.overallRating);
}
double Rating::clamp(double number)
{
    if (number < ONE)
        return ONE;
    else if (number > FIVE)
        return FIVE;
    else
        return number;
}
void Rating::clampAllElements()
{
    cleanliness = clamp(cleanliness);
    location = clamp(location);
    facilities = clamp(facilities);
    staff = clamp(staff);
    valueForMoney = clamp(valueForMoney);
}
Rating Rating::operator-=(std::vector<double> delta)
{
    location -= delta[0];
    cleanliness -= delta[1];
    staff -= delta[2];
    facilities -= delta[3];
    valueForMoney -= delta[4];
    return *this;
}
double Rating::getSumOfElements()
{
    return cleanliness + location + facilities + staff + valueForMoney;
}
double Rating::getError(Rating weights)
{
    return pow(getAverage(weights) - overallRating, 2);
}
double Rating::getAverage(Rating weights)
{
    Rating avg = *this * weights;
    return avg.getSumOfElements() / weights.getSumOfElements();
}
double Rating::getOverallRating()
{
    return overallRating;
}
void Rating::addEpsilon(int index, double epsilon)
{
    switch (index)
    {
    case 0:
        location += epsilon;
        break;
    case 1:
        cleanliness += epsilon;
        break;
    case 2:
        staff += epsilon;
        break;
    case 3:
        facilities += epsilon;
        break;
    case 4:
        valueForMoney += epsilon;
        break;
    }
}
void Rating::printAverageRating()
{
    cout << fixed << setprecision(2) << LOCATION << COLON << SPACE << location << endl
         << CLEANLINESS << COLON << SPACE << cleanliness << endl
         << STAFF << COLON << SPACE << staff << endl
         << FACILITIES << COLON << SPACE << facilities << endl
         << VALUE_FOR_MONEY << COLON << SPACE << valueForMoney << endl
         << OVERALL_RATING << COLON << SPACE << overallRating << endl;
}
double Rating::truncate(double x)
{
    return floor(x * 100) / (100);
}
void Rating::printManualWeights()
{
    cout << fixed << setprecision(2) << ACTIVE << SPACE << TRUE_STATE << SPACE << LOCATION << SPACE << truncate(location) << SPACE << CLEANLINESS << SPACE << truncate(cleanliness)
         << SPACE << STAFF << SPACE << truncate(staff) << SPACE << FACILITIES << SPACE << truncate(facilities) << SPACE << VALUE_FOR_MONEY << SPACE << truncate(valueForMoney) << SPACE << endl;
}
void Rating::printEstimatedWeights()
{
    cout << fixed << setprecision(2) << LOCATION << SPACE << truncate(location) << SPACE << CLEANLINESS << SPACE << truncate(cleanliness) << SPACE
         << STAFF << SPACE << truncate(staff) << SPACE << FACILITIES << SPACE << truncate(facilities) << SPACE << VALUE_FOR_MONEY << SPACE << truncate(valueForMoney) << endl;
}
bool Rating::isInvalid()
{
    return cleanliness < ONE || cleanliness > FIVE || facilities < ONE || facilities > FIVE || location < ONE || location > FIVE ||
           overallRating < ONE || overallRating > FIVE || staff < ONE || staff > FIVE || valueForMoney < ONE || valueForMoney > FIVE;
}
double Rating::getPartialDerivative(map<string, Rating> ratings, int index)
{
    double di = 0;
    double epsilon = EPSILON;
    Rating wprime = *this;
    wprime.addEpsilon(index, epsilon);
    for (auto rating : ratings)
    {
        di += (rating.second.getError(wprime) - rating.second.getError(*this)) / epsilon;
    }
    return di;
}
vector<double> Rating::getDeltas(map<string, Rating> ratings)
{
    vector<double> deltas;
    for (int i = 0; i < 5; i++)
    {
        deltas.push_back(getPartialDerivative(ratings, i));
    }
    return deltas;
}
