#ifndef DUPLICATE_NAME_H
#define DUPLICATE_NAME_H "DUPLICATE_NAME_H"

#include <exception>

class DuplicateName : public std::exception
{
public:
    const char *what() const throw();
};

#endif
