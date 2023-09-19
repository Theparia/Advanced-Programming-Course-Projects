#include "ManagementInterface.hpp"
#include "Exception.hpp"

using namespace std;

ManagementInterface::ManagementInterface(Utrip *utrip_)
{
    utrip = utrip_;
}
void ManagementInterface::parseCommand(string command)
{
    auto commandWords = split(command, 2);
    try
    {
        if (commandWords.size() != 2 && (commandWords[0] == POST || commandWords[0] == GET || commandWords[0] == DELETE))
            throw BadRequestException();
        if (commandWords[0] == POST)
            handlePostCommand(split(commandWords[1], 2));
        else if (commandWords[0] == GET)
            handleGetCommand(commandWords[1]);
        else if (commandWords[0] == DELETE)
            handleDeleteCommand(split(commandWords[1], 2));
        else
            throw BadRequestException();
    }
    catch (exception &ex)
    {
        cout << ex.what();
    }
}

void ManagementInterface::signup(vector<string> args)
{
    if (args.size() != 7)
        throw BadRequestException();
    string email, username, password;
    for (int i = 1; i < args.size(); i += 2)
    {
        if (args[i] == EMAIL)
            email = args[i + 1];
        else if (args[i] == USERNAME)
            username = args[i + 1];
        else if (args[i] == PASSWORD)
            password = args[i + 1];
        else
            throw BadRequestException();
    }
    utrip->signUpUser(email, username, password);
}

void ManagementInterface::login(vector<string> args)
{
    if (args.size() != 5)
        throw BadRequestException();
    string email, password;
    for (int i = 1; i < args.size(); i += 2)
    {
        if (args[i] == EMAIL)
            email = args[i + 1];
        else if (args[i] == PASSWORD)
            password = args[i + 1];
        else
            throw BadRequestException();
    }
    utrip->logIn(email, password);
}

void ManagementInterface::handlePostCommand(vector<string> args)
{
    if (args.size() != 2 && utrip->isLoggedIn() &&
        (args[0] == SIGNUP || args[0] == LOGIN || args[0] == WALLET || args[0] == RESERVES || args[0] == FILTERS || args[0] == COMMENTS || args[0] == RATINGS))
        throw BadRequestException();
    else if (args[0] == SIGNUP)
        signup(split(args[1], 7));
    else if (args[0] == LOGIN)
        login(split(args[1], 5));
    else if (!utrip->isLoggedIn())
        throw InaccessibilityException();
    else if (args[0] == LOGOUT)
        utrip->logOut();
    else if (args[0] == WALLET)
        chargeWallet(split(args[1], 3));
    else if (args[0] == RESERVES)
        bookRooms(split(args[1], 11));
    else if (args[0] == FILTERS)
        filterHotels(args[1]);
    else if (args[0] == COMMENTS)
        addComment(split(args[1], 5));
    else if (args[0] == RATINGS)
        addRating(split(args[1], 15));
    else
        throw NonExistenseException();
}
void ManagementInterface::handleDeleteCommand(vector<string> args)
{
    if (!utrip->isLoggedIn())
        throw InaccessibilityException();
    if (args[0] == FILTERS)
        utrip->deleteFilters();
    else if (args.size() != 2 && args[0] == RESERVES)
        throw BadRequestException();
    else if (args[0] == RESERVES)
        deleteReservation(split(args[1], 3));
    else
        throw NonExistenseException();
}
void ManagementInterface::deleteReservation(vector<string> args)
{
    if (args.size() != 3 || args[1] != ID)
        throw BadRequestException();
    utrip->deleteReservation(atoi(args[2].c_str()));
}
void ManagementInterface::bookRooms(vector<string> args)
{
    string hotelId, roomType;
    int quantity, checkIn, checkOut;
    if (args.size() != 11)
        throw BadRequestException();
    for (int i = 1; i < args.size(); i += 2)
    {
        if (args[i] == HOTEL)
            hotelId = args[i + 1];
        else if (args[i] == TYPE)
            roomType = args[i + 1];
        else if (args[i] == QUANTITY)
            quantity = atoi(args[i + 1].c_str());
        else if (args[i] == CHECK_IN)
            checkIn = atoi(args[i + 1].c_str());
        else if (args[i] == CHECK_OUT)
            checkOut = atoi(args[i + 1].c_str());
        else
            throw BadRequestException();
    }
    utrip->bookRooms(hotelId, roomType, quantity, Duration(checkIn, checkOut));
}
void ManagementInterface::handleGetCommand(string command)
{
    if (!utrip->isLoggedIn())
        throw InaccessibilityException();
    vector<string> commandWords = split(command, 2);
    if (commandWords.size() != 2 && (commandWords[0] == WALLET || commandWords[0] == COMMENTS || commandWords[0] == RATINGS))
        throw BadRequestException();
    else if (commandWords[0] == HOTELS)
        printHotelsInfo(command);
    else if (commandWords[0] == RESERVES)
        utrip->getReserves();
    else if (commandWords[0] == WALLET)
        printTurnover(split(commandWords[1], 3));
    else if (commandWords[0] == COMMENTS)
        getComments(split(commandWords[1], 3));
    else if (commandWords[0] == RATINGS)
        getRatings(split(commandWords[1], 3));
    else
        throw NonExistenseException();
}
void ManagementInterface::chargeWallet(vector<string> args)
{
    if (args.size() != 3 || args[1] != AMOUNT)
        throw BadRequestException();
    utrip->chargeWallet(stod(args[2].c_str()));
}
void ManagementInterface::printTurnover(vector<string> args)
{
    if (args.size() != 3 || args[1] != COUNT)
        throw BadRequestException();
    utrip->printTurnover(atoi(args[2].c_str()));
}
void ManagementInterface::printHotelsInfo(string arg)
{
    size_t found = arg.find("?");
    vector<string> commandWords = split(arg, 4);
    if (found != string::npos && commandWords.size() == 4 && commandWords[2] == ID)
    {
        utrip->printSpecifiedHotelInfo(commandWords[3]);
    }
    else if (found == string::npos && commandWords.size() == 1)
        utrip->printHotelsInfo();
    else
        throw BadRequestException();
}
vector<string> ManagementInterface::split(string command, size_t wordLimit)
{
    if (command[command.size() - 1] == '\n')
    {
        command = command.substr(0, command.size() - 1);
    }
    vector<string> splitCommand;
    size_t current, previous = 0;
    current = command.find(' ');
    while (current != string::npos && wordLimit > 1)
    {
        splitCommand.push_back(command.substr(previous, current - previous));
        previous = current + 1;
        current = command.find(' ', previous);
        wordLimit--;
    }
    splitCommand.push_back(command.substr(previous, std::string::npos - previous));
    return splitCommand;
}
void ManagementInterface::filterHotels(string arg)
{
    size_t city, minStar, minPrice, type;
    city = arg.find(CITY);
    minStar = arg.find(MIN_STAR);
    minPrice = arg.find(MIN_PRICE);
    type = arg.find(TYPE);
    if (city != string::npos)
        filterBasedOnCity(split(arg, 3));
    else if (minStar != string::npos)
        filterBasedOnStarRating(split(arg, 5));
    else if (minPrice != string::npos)
        filterBasedOnPrice(split(arg, 5));
    else if (type != string::npos)
        filterBasedOnDuration(split(arg, 9));
    else
        throw BadRequestException();
}
void ManagementInterface::filterBasedOnCity(vector<string> args)
{
    string city;
    if (args.size() != 3)
        throw BadRequestException();
    for (int i = 0; i < args.size(); i++)
    {
        if (args[i] == CITY)
            city = args[i + 1];
    }
    utrip->addCityFilter(city);
}
void ManagementInterface::filterBasedOnStarRating(vector<string> args)
{
    if (args.size() != 5)
        throw BadRequestException();
    int minStar, maxStar;
    for (int i = 1; i < args.size(); i += 2)
    {
        if (args[i] == MIN_STAR)
            minStar = atoi(args[i + 1].c_str());
        else if (args[i] == MAX_STAR)
            maxStar = atoi(args[i + 1].c_str());
        else
            throw BadRequestException();
    }
    utrip->addStarRatingFilter(minStar, maxStar);
}
void ManagementInterface::filterBasedOnPrice(vector<string> args)
{
    if (args.size() != 5)
        throw BadRequestException();
    double minimumPrice, maximumPrice;
    for (int i = 1; i < args.size(); i += 2)
    {
        if (args[i] == MIN_PRICE)
            minimumPrice = stod(args[i + 1].c_str());
        else if (args[i] == MAX_PRICE)
            maximumPrice = stod(args[i + 1].c_str());
        else
            throw BadRequestException();
    }
    utrip->addAveragePriceFilter(minimumPrice, maximumPrice);
}
void ManagementInterface::filterBasedOnDuration(vector<string> args)
{
    if (args.size() != 9)
        throw BadRequestException();
    string roomType;
    int quantity, checkIn, checkOut;
    for (int i = 1; i < args.size(); i += 2)
    {
        if (args[i] == TYPE)
            roomType = args[i + 1];
        else if (args[i] == QUANTITY)
            quantity = atoi(args[i + 1].c_str());
        else if (args[i] == CHECK_IN)
            checkIn = atoi(args[i + 1].c_str());
        else if (args[i] == CHECK_OUT)
            checkOut = atoi(args[i + 1].c_str());
        else
            throw BadRequestException();
    }
    utrip->addSpecialRoomsFilter(roomType, quantity, Duration(checkIn, checkOut));
}
void ManagementInterface::addComment(vector<string> args)
{
    if (args.size() != 5)
        throw BadRequestException();
    string hotelId, text;
    for (int i = 1; i < args.size(); i += 2)
    {
        if (args[i] == HOTEL)
            hotelId = args[i + 1];
        else if (args[i] == COMMENT)
            text = args[i + 1];
        else
            throw BadRequestException();
    }
    utrip->addComment(hotelId, text);
}
void ManagementInterface::getComments(vector<string> args)
{
    if (args.size() != 3 || args[1] != HOTEL)
        throw BadRequestException();
    utrip->printComments(args[2]);
}
void ManagementInterface::addRating(vector<string> args)
{
    if (args.size() != 15)
        throw BadRequestException();
    string hotelId;
    double location, cleanliness, staff, facilities, valueForMoney, overall;
    for (int i = 1; i < args.size(); i += 2)
    {
        if (args[i] == LOCATION)
            location = stod(args[i + 1].c_str());
        else if (args[i] == HOTEL)
            hotelId = args[i + 1];
        else if (args[i] == CLEANLINESS)
            cleanliness = stod(args[i + 1].c_str());
        else if (args[i] == STAFF)
            staff = stod(args[i + 1].c_str());
        else if (args[i] == FACILITIES)
            facilities = stod(args[i + 1].c_str());
        else if (args[i] == VALUE_FOR_MONEY)
            valueForMoney = stod(args[i + 1].c_str());
        else if (args[i] == OVERALL_RATING)
            overall = stod(args[i + 1].c_str());
        else
            throw BadRequestException();
    }
    utrip->addRating(hotelId, Rating(location, cleanliness, staff, facilities, valueForMoney, overall));
}
void ManagementInterface::getRatings(vector<string> args)
{
    if (args.size() != 3 || args[1] != HOTEL)
        throw BadRequestException();
    utrip->printAverageRating(args[2]);
}