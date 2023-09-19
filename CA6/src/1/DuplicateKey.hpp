#ifndef DUPLICATE_KEY_H
#define DUPLICATE_KEY_H "DUPLICATE_KEY_H"

#include <string>
#include <exception>

class DuplicateKey : public std::exception
{
public:
    const char *what() const throw();
};

#endif