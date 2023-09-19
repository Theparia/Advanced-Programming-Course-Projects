#include "Exception.hpp"
#include "StructsAndDefines.hpp"

using namespace std;

const char* NonExistenseException::what()const throw()
{
    return NOT_FOUND_EXCEPTION;
}
const char* BadRequestException::what()const throw()
{
    return BAD_REQUEST_EXCEPTION;
}
const char* InaccessibilityException::what()const throw()
{
    return INACCESSIBILITY_EXCEPTION;
}
const char* NotEnoughRoomException::what()const throw()
{
    return NOT_ENOUGH_ROOM_EXCEPTION;
}
const char* NotEnoughCreditException::what()const throw()
{
    return NOT_ENOUGH_CREDIT_EXCEPTION;
}