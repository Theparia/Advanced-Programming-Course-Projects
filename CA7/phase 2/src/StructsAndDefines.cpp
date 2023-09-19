#include "StructsAndDefines.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

Comment::Comment(string userName_, string text_)
{
    userName = userName_;
    text = text_;
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
