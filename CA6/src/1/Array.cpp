#include "Array.hpp"
#include <iostream>
#include "StringData.hpp"
#include "NumericData.hpp"

using namespace std;

#define NO_KEY ""
#define DOUBLE_QUOTATION "\""
#define IN_BRACKET "["
#define OUT_BRACKET "]"
#define COLON ":"
#define SPACE " "
#define COMMA ","
#define NEW_LINE "\n"

Array::Array(string key_, int id_)
{
    key = key_;
    id = id_;
}
int Array::getId()
{
    return id;
}
void Array::print(int parentId)
{
    tab++;
    if (isThereKey())
        cout << DOUBLE_QUOTATION << key << DOUBLE_QUOTATION<<COLON<<SPACE;
    cout << IN_BRACKET;
    if (datas.size() != 0)
        cout << NEW_LINE;
    for (int i = 0; i < datas.size(); i++)
    {
        printTab();
        datas[i]->print(parentId);
        if (i != datas.size() - 1)
            cout << COMMA<<NEW_LINE;
        else
            cout <<NEW_LINE;
    }
    tab--;
    if (datas.size() != 0)
    {
        printTab();
    }
    cout << OUT_BRACKET;
}
void Array::addString(string value)
{
    StringData *stringData = new StringData(NO_KEY, value);
    datas.push_back(stringData);
}
void Array::addInteger(int value)
{
    NumericData *numericData = new NumericData(NO_KEY, value);
    datas.push_back(numericData);
}
void Array::addContainer(Data *data)
{
    datas.push_back(data);
}