#include "Nonexistence.hpp"

#define NONEXISTENCE_ERROR "Channel does not exist\n"

const char* Nonexistence::what() const throw()
{
    return NONEXISTENCE_ERROR;
}