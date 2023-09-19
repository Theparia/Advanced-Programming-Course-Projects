#ifndef INVALID_ID_H
#define INVALID_ID_H "INVALID_ID_H"

#include <exception>
#include <string>

class InvalidId : public std::exception
{
public:
    const char* what()const throw();
};

#endif