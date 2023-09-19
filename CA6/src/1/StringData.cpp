#include "StringData.hpp"
#include <iostream>

using namespace std;

#define DOUBLE_QUOTATION "\""
#define NO_KEY ""
#define COLON ":"
#define SPACE " "

StringData::StringData(string key_, string value_)
{
    key = key_;
    value = value_;
}
void StringData::print(int parentId)
{
    if (isThereKey())
        cout << DOUBLE_QUOTATION << key << DOUBLE_QUOTATION<<COLON<<SPACE;
    cout << DOUBLE_QUOTATION << value <<DOUBLE_QUOTATION;
}