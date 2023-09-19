#ifndef UNDEFINED_TYPE_H
#define UNDEFINED_TYPE_H "UNDEFINED_TYPE_H"

#include <exception>
#include <string>

class UndefinedType : public std::exception
{
public:
    const char* what()const throw();
};

#endif