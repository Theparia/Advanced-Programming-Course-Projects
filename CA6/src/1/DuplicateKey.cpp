#include "DuplicateKey.hpp"

using namespace std;

#define DUPLICATE_KEY_ERROR "Duplicate key.\n"

const char* DuplicateKey::what()const throw()
{
    return DUPLICATE_KEY_ERROR;
}