#ifndef NONEXISTENCE_H
#define NONEXISTENCE_H "NONEXISTENCE_H"

#include <exception>

class Nonexistence : public std::exception
{
public:
    const char *what() const throw();
};

#endif