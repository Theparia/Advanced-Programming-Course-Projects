#ifndef STRING_DATA_H
#define STRING_DATA_H "STRING_DATA_H"

#include "Data.hpp"
#include <string>

class StringData:public Data
{
private:
    std::string value;
public:
    StringData(std::string key_,std::string value_);
    void print(int parentId);
};
#endif