#include "UndefinedType.hpp"

using namespace std;

#define UNDEFINED_TYPE_ERROR "Undefined type.\n"

const char* UndefinedType::what()const throw()
{
    return UNDEFINED_TYPE_ERROR;
}