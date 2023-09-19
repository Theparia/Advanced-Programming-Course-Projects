#include "Review.hpp"
#include <iostream>
using namespace std;
Review::Review(int init_id,int init_book_id, int init_user_id, int init_rating, string init_date, int init_number_of_likes)
{
	id = init_id;
	book_id=init_book_id;
	user_id = init_user_id;
	rating = init_rating;
	date = init_date;
	number_of_likes = init_number_of_likes;
}
int Review::get_id() 
{ 
	return id; 
}
int Review::get_book_id()
{
	return book_id;
}
int Review::get_number_of_likes()
{
	return number_of_likes;
}
int Review::get_user_id()
{
	return user_id;
}
int Review::get_rating()
{
	return rating;
}
void Review::show()
{
	cout<<"id: "<<id<<" Rating: "<<rating<<" Likes: "<<number_of_likes<<" Date: "<<date<<endl;
}