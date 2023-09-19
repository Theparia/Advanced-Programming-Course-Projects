#ifndef NUMERIC_DATA_H
#define NUMERIC_DATA_H "NUMERIC_DATA_H"

#include "Data.hpp"
#include <string>

class NumericData : public Data
{
private:
    int value;

public:
    NumericData(std::string key_,int value_);
    void print(int parentId);
};
#endif