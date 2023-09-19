#include "JsonBuilder.hpp"
#include <iostream>
#include "InvalidId.hpp"
#include "UndefinedType.hpp"
#include "DuplicateKey.hpp"

using namespace std;

#define NO_KEY ""
#define ARRAY_TYPE "array"
#define OBJECT_TYPE "object"

int JsonBuilder::idNumber = 0;

JsonBuilder::JsonBuilder()
{
    Object *parent = new Object(0, NO_KEY);
    objects.push_back(parent);
}
Object *JsonBuilder::findObjectById(int id)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getId() == id)
            return objects[i];
    }
    throw InvalidId();
}
Array *JsonBuilder::findArrayById(int id)
{
    for (int i = 0; i < arrays.size(); i++)
    {
        if (arrays[i]->getId() == id)
            return arrays[i];
    }
    throw InvalidId();
}
void JsonBuilder::addStringToObject(int parentId, string key, string value)
{
    Object *object = findObjectById(parentId);
    if (object->isKeyDuplicated(key))
        throw DuplicateKey();
    else
        object->addString(key, value);
}
void JsonBuilder::print(int id)
{
    findObjectById(id)->print(id);
    cout << endl;
}
void JsonBuilder::addIntegerToObject(int parentId, string key, int value)
{
    Object *object = findObjectById(parentId);
    if (object->isKeyDuplicated(key))
        throw DuplicateKey();
    else
        object->addInteger(key, value);
}
void JsonBuilder::produceIdNumber()
{
    idNumber++;
}
void JsonBuilder::addObjectToObject(int parentId, string key)
{
    if (findObjectById(parentId)->isKeyDuplicated(key))
        throw DuplicateKey();
    else
    {
        Object *object = new Object(idNumber, key);
        findObjectById(parentId)->addContainer(object);
        objects.push_back(object);
    }
}
void JsonBuilder::addArrayToObject(int parentId, string key)
{
    if (findObjectById(parentId)->isKeyDuplicated(key))
        throw DuplicateKey();
    else
    {
        Array *array = new Array(key, idNumber);
        findObjectById(parentId)->addContainer(array);
        arrays.push_back(array);
    }
}
int JsonBuilder::addContainerToObject(int parentId, string key, string type)
{
    produceIdNumber();
    if (type == OBJECT_TYPE)
        addObjectToObject(parentId, key);
    else if (type == ARRAY_TYPE)
        addArrayToObject(parentId, key);
    else
        throw UndefinedType();
    return idNumber;
}
void JsonBuilder::addObjectToArray(int parentId)
{
    Object *object = new Object(idNumber, NO_KEY);
    findArrayById(parentId)->addContainer(object);
    objects.push_back(object);
}
void JsonBuilder::addArrayToArray(int parentId)
{
    Array *array = new Array(NO_KEY, idNumber);
    findArrayById(parentId)->addContainer(array);
    arrays.push_back(array);
}
int JsonBuilder::addContainerToArray(int parentId, string type)
{
    produceIdNumber();
    if (type == OBJECT_TYPE)
        addObjectToArray(parentId);
    else if (type == ARRAY_TYPE)
       addArrayToArray(parentId);
    else
        throw UndefinedType();
    return idNumber;
}
void JsonBuilder::addStringToArray(int parentId, string value)
{

    findArrayById(parentId)->addString(value);
}
void JsonBuilder::addIntegerToArray(int parentId, int value)
{

    findArrayById(parentId)->addInteger(value);
}
