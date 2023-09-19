#ifndef USER_H
#define USER_H "USER_H"
#include <vector>
#include <string>
class Author;
class Book;
class Review;
class User
{
private:
	int id,likes;
	std::string name;
	std::string place_of_birth;
	std::string member_since;
	std::vector <Author*> favorite_authors;
	std::vector <std::string> favorite_genres;
	std::vector <Book*> want_to_read;
	std::vector <Book*> currently_reading;
	std::vector <Book*> read;
	std::vector <User*> followings;
    std::vector <Review*> reviews;
public:
    User(int init_id,std::string init_name,std:: string init_place_of_birth,std:: string init_member_since,std:: vector <Author*> init_favorite_authors,std:: vector <std::string> init_favorite_genres,std:: vector <Book*> init_want_to_read, std::vector <Book*> init_currently_reading,std:: vector <Book*> init_read);
    std::vector <User*> get_followings();
    std::vector <std::string> get_favorite_genres();
    int get_likes();
    std::string get_name();
    int get_id();
    std::vector <Book*> get_want_to_read();
    std::vector <Book*> get_currently_reading();
    std::vector <Book*> get_read();
    std::vector <Review*> get_reviews();
    void add_review(Review* review);
    static bool compare_titles(Book* b1, Book* b2);
    std::vector <Book*> get_sorted_books(std::vector <Book*> books, std::string genre);
    double calculate_user_credit(double number_of_user_reviews_like,double number_of_likes,double number_of_user_reviews,double number_of_reviews);
    void set_likes(int new_likes);
    static bool compare_genres(std::string s1,std::string s2);
    static bool compare_authors(Author* a1,Author* a2);
    void show_best_reviewer();
    void set_followings(std::vector <User*> new_followings);
    void show_sorted_shelf(std::string shelf_type,std::string genre);
    int get_number_of_user_reviews_likes();
};

#endif