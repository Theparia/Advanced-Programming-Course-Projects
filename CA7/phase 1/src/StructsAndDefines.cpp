#include "StructsAndDefines.hpp"

using namespace std;

Comment::Comment(string userName_, string text_)
{
    userName = userName_;
    text = text_;
}
Rating::Rating(double location_, double cleanliness_, double staff_, double facilities_, double valueForMoney_, double overallRating_)
{
    location = location_;
    cleanliness = cleanliness_;
    staff = staff_;
    facilities = facilities_;
    valueForMoney = valueForMoney_;
    overallRating = overallRating_;
}
Duration::Duration(int checkIn_, int checkOut_)
{
    checkIn = checkIn_;
    checkOut = checkOut_;
}
bool Duration::operator==(const Duration &duration) const
{
    return (duration.checkIn == checkIn) && (duration.checkOut == checkOut);
}