#include "Book.hpp"
#include "Author.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Book::Book(int init_id, string init_title, Author* init_author, string init_genre)
{
	id = init_id;
	title = init_title;
	author = init_author;
	genre = init_genre;
	rating=0;
}
int Book::get_id() 
{ 
	return id; 
}
string Book::get_title() 
{ 
	return title; 
}
string Book::get_genre() 
{ 
	return genre;
}
Author* Book::get_author() 
{ 
	return author; 
}
double Book::get_rating()
{
	return rating;
}
vector <Review*> Book:: get_reviews()
{
	return reviews;
}
void Book::add_review(Review* review)
{
	reviews.push_back(review);
}
void Book::set_rating(double new_rating)
{
	rating =new_rating;
}
void Book::show_book_info_in_shelf()
{
	cout << "id: " << id << endl << "Title: " << title << endl << "Genre: ";
	cout << genre << endl << "Author: " << author->get_name() << endl;
}
double Book::calculate_avg_rating()
{
	double ratings=0;
	if(reviews.size()==0)
		return 0;
	for(int i=0;i<reviews.size();i++)
	{
		ratings+=reviews[i]->get_rating();		
	}
	return (ratings/reviews.size());
}
void Book::show_best_book()
{
	cout<<"id: "<<id<<endl<<"Title: "<<title<<endl<<"Genre: "<<genre<<endl<<"Author: ";
	cout<<author->get_name()<<endl<<"Average Rating: "<<fixed<<setprecision(2)<<rating<<endl;
}
void Book::show_author_book()
{
	cout << "id: " <<id<< " Title: " <<title<< endl;
}
