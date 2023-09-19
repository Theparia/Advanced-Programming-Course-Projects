#include "Object.hpp"
#include "StringData.hpp"
#include "NumericData.hpp"
#include <iostream>

using namespace std;

#define NO_KEY ""
#define DOUBLE_QUOTATION "\""
#define IN_BRACE "{"
#define OUT_BRACE "}"
#define COMMA ","
#define SPACE " "
#define NEW_LINE "\n"
#define COLON ":"

Object::Object(int id_, string key_)
{
    id = id_;
    key = key_;
}
int Object::getId()
{
    return id;
}
void Object::addString(string stringKey, string value)
{
    StringData *stringData = new StringData(stringKey, value);
    datas.push_back(stringData);
}
void Object::print(int parentId)
{
    tab++;
    if (isThereKey() && parentId!=id)
        cout << DOUBLE_QUOTATION << key << DOUBLE_QUOTATION<<COLON<<SPACE;
    cout << IN_BRACE;
    if (datas.size() != 0)
        cout << NEW_LINE;
    for (int i = 0; i < datas.size(); i++)
    {
        printTab();
        datas[i]->print(parentId);
        if (i != datas.size() - 1)
            cout << COMMA<<NEW_LINE;
        else
            cout << endl;
    }
    tab--;
    if (datas.size() != 0)
    {
        printTab();
    }
    cout << OUT_BRACE;
}
void Object::addInteger(std::string integerKey, int value)
{
    NumericData *numericData = new NumericData(integerKey, value);
    datas.push_back(numericData);
}
void Object::addContainer(Data *data)
{
    datas.push_back(data);
}
bool Object::isKeyDuplicated(string anotherKey)
{
    for(int i=0;i<datas.size();i++)
    {
        if(datas[i]->getKey()==anotherKey)
        return true;
    }
    return false;
}