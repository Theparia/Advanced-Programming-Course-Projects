#ifndef OBJECT_H
#define OBJECT_H "OBJECT_H"

#include "Data.hpp"
#include <vector>
#include <string>


class JsonBuilder;
class Object : public Data
{
private:
    int id;
    JsonBuilder* jsonBuilder;
    std::vector<Data *> datas;

public:
    Object(int id_, std::string key_);
    int getId();
    void print(int parentId);
    void addString(std::string stringKey, std::string value);
    void addInteger(std::string integerKey, int value);
    virtual void addContainer(Data* data);
    bool isKeyDuplicated(std::string anotherKey);
};

#endif