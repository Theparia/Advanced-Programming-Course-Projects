#include "CSVReader.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> CSVReader::parseData(string info, char delimiter)
{
    string line;
    vector<string> data;
    stringstream file(info);
    while (getline(file, line, delimiter))
    {
        data.push_back(line);
    }
    return data;
}
vector<Hotel *> CSVReader::readHotelsData(string filePath)
{
    vector<Hotel *> hotels;
    ifstream file(filePath);
    string ignored, data;
    getline(file, ignored, NEW_LINE);
    while (getline(file, data, NEW_LINE))
    {
        hotels = addHotel(data, hotels);
    }
    return hotels;
}
map<string, Rating> CSVReader::readRatingsData(string filePath)
{
    map<string, Rating> ratings;
    ifstream file(filePath);
    string ignored, data;
    getline(file, ignored, NEW_LINE);
    while (getline(file, data, NEW_LINE))
    {
        vector<string> info = parseData(data, COMMA);
        ratings[info[0]] = Rating(stod(info[1].c_str()), stod(info[2].c_str()), stod(info[3].c_str()), stod(info[4].c_str()), stod(info[5].c_str()), stod(info[6].c_str()));
    }
    return ratings;
}
vector<Hotel *> CSVReader::addHotel(string info, vector<Hotel *> hotels)
{
    vector<string> data = parseData(info, COMMA);
    Hotel *hotel = new Hotel(data[0], data[1], atoi(data[2].c_str()), data[3], data[4], data[5], stod(data[6].c_str()),
                             stod(data[7].c_str()), data[8], getTotalRooms(data));
    hotel->setPrices(stod(data[13].c_str()), stod(data[14].c_str()), stod(data[15].c_str()), stod(data[16].c_str()));
    hotels.push_back(hotel);
    return hotels;
}
void CSVReader::addRooms(int number, string type, vector<Room *> &rooms)
{
    char firstLetter = type[0];
    for (int i = 0; i < number; i++)
    {
        Room *room = new Room(firstLetter + to_string(i + 1), type);
        rooms.push_back(room);
    }
}
vector<Room *> CSVReader::getTotalRooms(const vector<string> &data)
{
    vector<Room *> rooms;
    addRooms(atoi(data[9].c_str()), STANDARD_TYPE, rooms);
    addRooms(atoi(data[10].c_str()), DELUXE_TYPE, rooms);
    addRooms(atoi(data[11].c_str()), LUXURY_TYPE, rooms);
    addRooms(atoi(data[12].c_str()), PREMIUM_TYPE, rooms);
    return rooms;
}