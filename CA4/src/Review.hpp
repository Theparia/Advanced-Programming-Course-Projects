#ifndef REVIEW_H
#define REVIEW_H "REVIEW_H"
#include <string>
class Review
{
private:
	int id;
    int book_id;
    int user_id;
	int rating;
	std::string date;
	int number_of_likes;
public:
    Review(int init_id,int init_book_id,int init_user_id, int init_rating,std:: string init_date, int init_number_of_likes);
    int get_id();
    int get_book_id();
    int get_number_of_likes();
    int get_user_id();
    int get_rating();
    void show();
};
#endif