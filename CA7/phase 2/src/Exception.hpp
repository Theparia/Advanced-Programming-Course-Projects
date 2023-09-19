#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_ "_EXCEPTION_H_"

using namespace std;

#include <exception>

class NonExistenseException : public std::exception
{
public:
    const char *what() const throw();
};
class BadRequestException : public std::exception
{
public:
    const char *what() const throw();
};
class InaccessibilityException : public std::exception
{
public:
    const char *what() const throw();
};
class NotEnoughRoomException : public std::exception
{
public:
    const char *what() const throw();
};
class NotEnoughCreditException : public std::exception
{
public:
    const char *what() const throw();
};
class InsufficientRatingsException : public std::exception
{
public:
    const char *what() const throw();
};

#endif