#include "DuplicateName.hpp"

using namespace std;

#define DUPLICATE_NAME_ERROR "Channel already exists\n"

const char* DuplicateName::what() const throw()
{
    return DUPLICATE_NAME_ERROR;
}