#ifndef _STRUCTS_AND_DEFINES_H_
#define _STRUCTS_AND_DEFINES_H_ "_STRUCTS_AND_DEFINES_H_"

#include <string>
#include <vector>

#define NOT_FOUND_EXCEPTION "Not Found\n"
#define BAD_REQUEST_EXCEPTION "Bad Request\n"
#define INACCESSIBILITY_EXCEPTION "Permission Denied\n"
#define NOT_ENOUGH_ROOM_EXCEPTION "Not Enough Room\n"
#define NOT_ENOUGH_CREDIT_EXCEPTION "Not Enough Credit\n"
#define INSUFFICIENT_RATINGS_EXCEPTION "Insufficient Ratings\n"
#define STANDARD_TYPE "standard"
#define DELUXE_TYPE "deluxe"
#define LUXURY_TYPE "luxury"
#define PREMIUM_TYPE "premium"
#define SPACE ' '
#define NO_RATING "No Rating\n"
#define POST "POST"
#define GET "GET"
#define DELETE "DELETE"
#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define SIGNUP "signup"
#define LOGIN "login"
#define LOGOUT "logout"
#define WALLET "wallet"
#define RESERVES "reserves"
#define FILTERS "filters"
#define COMMENTS "comments"
#define RATINGS "ratings"
#define ID "id"
#define HOTEL "hotel"
#define QUANTITY "quantity"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define TYPE "type"
#define HOTELS "hotels"
#define AMOUNT "amount"
#define COUNT "count"
#define CITY "city"
#define MIN_STAR "min_star"
#define MAX_STAR "max_star"
#define MIN_PRICE "min_price"
#define MAX_PRICE "max_price"
#define COMMENT "comment"
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define OVERALL_RATING "overall_rating"
#define EMPTY "Empty\n"
#define OK "OK\n"
#define ONE 1
#define TWO 2
#define FIVE 5
#define ZERO 0
#define TEN 10
#define NEW_LINE '\n'
#define COMMA ','
#define COLON ':'
#define QUESTION_MARK "?"
#define STAR "star"
#define OVERVIEW "overview"
#define AMENITIES "amenities"
#define ROOMS "#rooms"
#define LATITUDE "latitude"
#define LONGITUDE "longitude"
#define PRICE "price"
#define VALUE_FOR_MONEY_PHRASE "value for money"
#define OVERALL_RATING_PHRASE "overall rating"
#define ROOM "room"
#define COST "cost"
#define ASCENDING_ORDER "ascending"
#define DESCENDING_ORDER "descending"
#define STANDARD_ROOM_PRICE "standard_room_price"
#define DELUXE_ROOM_PRICE "deluxe_room_price"
#define LUXURY_ROOM_PRICE "luxury_room_price"
#define PREMIUM_ROOM_PRICE "premium_room_price"
#define HOTEL_NAME "name"
#define STAR_RATING "star_rating"
#define PERSONAL_RATING "rating_personal"
#define AVERAGE_ROOM_PRICE "average_room_price"
#define RATINGS_FILE "file"
#define TRUE_STATE "true"
#define FALSE_STATE "false"
#define DEFAULT_PRICE_FILTER_PHRASE "* Results have been filtered by the default price filter.\n"
#define SORT "sort"
#define DEFAULT_PRICE_FILTER "default_price_filter"
#define MANUAL_WEIGHTS "manual_weights"
#define ESTIMATED_WEIGHTS "estimated_weights"
#define ACTIVE "active"
#define ORDER "order"
#define PROPERTY "property"
#define EPSILON 0.0001

struct Comment
{
    std::string userName;
    std::string text;
    Comment(std::string userName_, std::string text_);
};
enum filterType
{
    City,
    StarRating,
    AveragePrice,
    DurationOfStay,
    DefaultPrice
};
struct Duration
{
    int checkIn;
    int checkOut;
    Duration(int checkIn_, int checkOut_);
    Duration() {}
    bool operator==(const Duration &duration) const;
};
struct Wallet
{
    double accountBalance;
    std::vector<double> turnover;
};

#endif