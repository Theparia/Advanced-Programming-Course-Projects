#ifndef SAME_SRC_AND_DST_H
#define SAME_SRC_AND_DST_H "SAME_SRC_AND_DST_H"

#include <exception>

class SameSrcAndDst : public std::exception
{
public:
    const char *what() const throw();
};

#endif