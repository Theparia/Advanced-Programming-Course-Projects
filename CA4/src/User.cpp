#include "User.hpp"
#include "Book.hpp"
#include "Author.hpp"
#include "Review.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

#define WANT_TO_READ_TYPE_NAME "want_to_read"
#define CURRENTLY_READING_TYPE_NAME "currently_reading"
#define READ_TYPE_NAME "read"

User::User(int init_id, string init_name, string init_place_of_birth, string init_member_since, vector <Author*> init_favorite_authors, vector <string> init_favorite_genres, vector <Book*> init_want_to_read, vector <Book*> init_currently_reading, vector <Book*> init_read)
{
	id = init_id;
	name = init_name;
	place_of_birth = init_place_of_birth;
	member_since = init_member_since;
	favorite_authors = init_favorite_authors;
	favorite_genres = init_favorite_genres;
	want_to_read = init_want_to_read;
	currently_reading = init_currently_reading;
	read = init_read;
}
vector <User*> User::get_followings()
{
	return followings;
}
vector <string> User::get_favorite_genres()
{
	return favorite_genres;
}
int User::get_likes()
{
	return likes;
}
string User::get_name() 
{ 
	return name; 
}
int User::get_id() 
{ 
	return id; 
}
vector <Book*> User::get_want_to_read() 
{ 
	return want_to_read; 
}
vector <Book*> User::get_currently_reading() 
{ 
	return currently_reading; 
}
vector <Book*> User::get_read() 
{ 
	return read; 
}
vector <Review*> User::get_reviews()
{
	return reviews;
}
void User::add_review(Review* review)
{
	reviews.push_back(review);
}
bool User::compare_titles(Book* b1, Book* b2)
{
    if(b1->get_title()==b2->get_title())
        return b1->get_id() < b2->get_id();
	return b1->get_title() < b2->get_title();
}
vector <Book*> User::get_sorted_books(vector <Book*> books, string genre)
{
	sort(books.begin(), books.end(), compare_titles);
	vector <Book*> sorted;
	for (int i = 0; i<books.size(); i++)
	{
		if (books[i]->get_genre() == genre)
			sorted.push_back(books[i]);
	}
	for (int i = 0; i<books.size(); i++)
	{
		if (books[i]->get_genre() != genre)
			sorted.push_back(books[i]);
	}
	return sorted;

}
void User::show_sorted_shelf(string shelf_type, string genre)
{
	vector <Book*> shelf;
	if (shelf_type == WANT_TO_READ_TYPE_NAME)
	{
		shelf = get_sorted_books(want_to_read, genre);
	}
	if (shelf_type == CURRENTLY_READING_TYPE_NAME)
	{
		shelf = get_sorted_books(currently_reading, genre);
	}
	if (shelf_type == READ_TYPE_NAME)
	{
		shelf = get_sorted_books(read, genre);
	}
	for (int i = 0; i<shelf.size(); i++)
	{
		shelf[i]->show_book_info_in_shelf();
		cout << "***" << endl;
	}
}
double User::calculate_user_credit(double number_of_user_reviews_like,double number_of_likes,double number_of_user_reviews,double number_of_reviews)
{
	double credit,likes_fraction,reviews_fraction;
	likes_fraction=number_of_user_reviews_like/number_of_likes;
	reviews_fraction=number_of_user_reviews/number_of_reviews;
    if(number_of_likes==0)
		likes_fraction=0;
	if(number_of_reviews==0)
		reviews_fraction=0;
    credit=(likes_fraction+reviews_fraction)/2;
    return credit;
}
void User::set_likes(int new_likes)
{
	likes=new_likes;
}
int User::get_number_of_user_reviews_likes()
{
	int likes_no=0;
	for(int i=0;i<reviews.size();i++)
	{
		likes_no+=reviews[i]->get_number_of_likes();
	}
	return likes_no;
}
bool User::compare_genres(string s1,string s2)
{
	return s1 < s2;
}
bool User::compare_authors(Author* a1,Author* a2)
{
	return a1->get_id() < a2->get_id();
}
void User::show_best_reviewer()
{
	cout<<"id: "<<id<<endl<<"Name: "<<name<<endl<<"Place of Birth: "<<place_of_birth<<endl<<"Member Since: "<<member_since<<endl<<"Favorite Genres: ";
	sort(favorite_genres.begin(),favorite_genres.end(),compare_genres);
	for(int i=0;i<favorite_genres.size();i++)
	{
		cout<<favorite_genres[i];
		if(i!=favorite_genres.size()-1)
			cout<<", ";
	}
	cout<<endl<<"Favorite Authors: ";
	sort(favorite_authors.begin(),favorite_authors.end(),compare_authors);
	for(int i=0;i<favorite_authors.size();i++)
	{
		cout<<favorite_authors[i]->get_name();
		if(i!=favorite_authors.size()-1)
			cout<<", ";
	}
	cout<<endl<<"Number of Books in Read Shelf: "<<read.size()<<endl;
	cout<<"Number of Books in Want to Read Shelf: "<<want_to_read.size()<<endl;
	cout<<"Number of Books in Currently Reading Shelf: "<<currently_reading.size()<<endl;
	cout<<"Number of Likes: "<<likes<<endl;
}
void User::set_followings(vector <User*> new_followings)
{
	followings=new_followings;
}