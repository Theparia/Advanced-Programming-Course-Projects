#ifndef _RATING_H_
#define _RATING_H_ "_RATING_H_"

#include <vector>
#include <map>
#include <string>

class Rating
{
private:
    double location;
    double cleanliness;
    double staff;
    double facilities;
    double valueForMoney;
    double overallRating;

public:
    Rating(double location_, double cleanliness_, double staff_, double facilities_, double valueForMoney_, double overallRating_);
    Rating() {}
    Rating operator*(Rating rating);
    void clampAllElements();
    double clamp(double number);
    Rating operator-=(std::vector<double> delta);
    double getError(Rating wights);
    double getAverage(Rating weights);
    double getSumOfElements();
    void addEpsilon(int index, double epsilon);
    void printAverageRating();
    void printManualWeights();
    void printEstimatedWeights();
    bool isInvalid();
    double getOverallRating();
    double getPartialDerivative(std::map<std::string, Rating> ratings, int i);
    std::vector<double> getDeltas(std::map<std::string, Rating> ratings);
    double truncate(double number);
};

#endif