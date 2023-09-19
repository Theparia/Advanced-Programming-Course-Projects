#include "SameSrcAndDst.hpp"

#define SAME_SRC_AND_DST_ERROR "Source and destination cannot be the same channel\n"

const char * SameSrcAndDst::what() const throw()
{
    return SAME_SRC_AND_DST_ERROR;
}