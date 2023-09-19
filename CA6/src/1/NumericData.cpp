#include "NumericData.hpp"
#include <iostream>

using namespace std;

#define NO_KEY ""
#define DOUBLE_QUOTATION "\""
#define COLON ":"
#define SPACE " "

NumericData::NumericData(string key_, int value_)
{
    key = key_;
    value = value_;
}

void NumericData::print(int parentId)
{
    if (isThereKey())
        cout << DOUBLE_QUOTATION << key << DOUBLE_QUOTATION << COLON << SPACE;
    cout << value;
}