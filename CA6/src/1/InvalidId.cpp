#include "InvalidId.hpp"

using namespace std;

#define INVALID_ID_ERROR "Invalid id.\n"

const char *InvalidId::what() const throw()
{
    return INVALID_ID_ERROR;
}