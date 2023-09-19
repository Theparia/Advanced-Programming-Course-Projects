#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

typedef vector <int> PreID;
struct Time 
{
	string day;
	int start_hour;
	int end_hour;
	int start_min;
	int end_min;
};
typedef vector <Time> TimeTable;
struct Course 
{
	int ID;
	string name;
	int units;
	TimeTable schedule;
	PreID prerequisites;

};

struct Grade 
{
	int ID;
	float grade;
};

typedef vector <Course> CourseTable;
typedef vector <Grade> GradeTable;

CourseTable read_course_info(string address);
void insert_schedule_to_CourseTable(CourseTable &courses,string time_table,Course *new_course);
void insert_prerequisties_to_CourseTable(CourseTable &courses,string pre_courses,Course *new_course);
int string_to_int(string address);
float string_to_float(string input);
GradeTable read_grades(string address);
vector<string> sort_alphabetically(CourseTable valid_courses);
bool has_already_passed_course(Course x, GradeTable y);
bool has_passed_prequisite(Course x, GradeTable y,int index);
bool has_passed_all_prequisites(Course x, GradeTable y);
CourseTable find_takable_courses(CourseTable x, GradeTable y);
void generate_output(CourseTable valid_courses);


int main(int argc,char* argv[]) 
{
	CourseTable courses = read_course_info(argv[1]);
	GradeTable grades = read_grades(argv[2]);
	CourseTable valid_courses= find_takable_courses(courses,grades);
	generate_output(valid_courses);
}

CourseTable read_course_info(string address) 
{
	ifstream file;
	CourseTable courses;
    Course *new_course;
	string ID, units;
	string time_table,pre_courses ;
	file.open(address);
	if (!file)
		cout << "unable to open courses file!\n";
	else {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		while(getline(file, ID, ',')) 
        {
            new_course=new Course;
			new_course->ID = string_to_int(ID);
			getline(file, new_course->name, ',');
			getline(file, units, ',');
			new_course->units = string_to_int(units);
			getline(file, time_table, ',');
			getline(file, pre_courses);
            insert_schedule_to_CourseTable(courses,time_table,new_course);
            insert_prerequisties_to_CourseTable(courses,pre_courses,new_course);
            courses.push_back(*new_course);
            delete new_course;
		}
	}	
	file.close();
	return courses;
}
void insert_schedule_to_CourseTable(CourseTable &courses,string time_table,Course *new_course)
{
    Time *new_time;
    vector <string> schedule;
    stringstream schedule_stream;
    schedule_stream<<time_table;
    string time;
    while(getline(schedule_stream,time,'/'))
    {
        schedule.push_back(time);
    }
    for(int i=0;i<schedule.size();i++)
    {
        new_time=new Time;
        stringstream ss;
        char ch;
        ss<<schedule[i];
        new_time->day = schedule[i].substr(0, 3);
        ss>>ch>>ch>>ch>>ch>>new_time->start_hour>>ch>>new_time->start_min>>ch>>new_time->end_hour>>ch>>new_time->end_min;
        new_course->schedule.push_back(*new_time);
        stringstream().swap(ss);
		delete new_time;
    }
}
void insert_prerequisties_to_CourseTable(CourseTable &courses,string pre_courses,Course *new_course)
{
    stringstream prerequisties_stream;
    prerequisties_stream<<pre_courses;
    string pre_id;
    while(getline(prerequisties_stream,pre_id,'-'))
    {
        new_course->prerequisites.push_back(string_to_int(pre_id));
    }
}

int string_to_int(string input)
 {
	stringstream converter;
	int x;
	converter << input;
	converter >> x;
	return x;
}

GradeTable read_grades(string address) 
{
	ifstream file;
	GradeTable grades;
	Grade *new_grade;
	file.open(address);
	string ID, grade;
	if (!file)
		cout << "unable to open grades file!\n";
	else 
    {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		while (getline(file, ID, ',')) 
        {
			new_grade = new Grade;
			new_grade->ID = string_to_int(ID);
			getline(file,grade);
			new_grade->grade = string_to_float(grade);
			grades.push_back(*new_grade);
			delete new_grade;
		}
	}
	file.close();
	return grades;

}
float string_to_float(string input)
{
	stringstream converter;
	float x;
	converter << input;
	converter >> x;
	return x;
}
CourseTable find_takable_courses(CourseTable courses, GradeTable grades) 
{
	CourseTable valid_courses;
	for (int i = 0; i <courses.size(); i++) 
    {
		if (has_already_passed_course(courses[i], grades) == 0 && has_passed_all_prequisites(courses[i], grades) == 1)
			valid_courses.push_back(courses[i]);

	}
	return valid_courses;
}
bool has_already_passed_course(Course x, GradeTable grades) 
{
	for (int i = 0; i < grades.size(); i++) 
    {
		if (x.ID == grades[i].ID && grades[i].grade >= 10)
			return true;
	}
	return false;
}
bool has_passed_prequisite(Course x, GradeTable grades,int index) 
{
		for (int i = 0; i < grades.size(); i++) 
        {
			if (x.prerequisites[index] == grades[i].ID && grades[i].grade >= 10)
            {
				return true;   
            }
		}
    
	return false;
}
bool has_passed_all_prequisites(Course x, GradeTable grades)
{
    if(x.prerequisites.size()==1 && x.prerequisites[0]==0)
    return true;
    else
    {
         for(int i=0;i<x.prerequisites.size();i++)
         {
            if (has_passed_prequisite(x,grades,i)==0)
            return false;
        }
    return true;
    }

}
void generate_output(CourseTable valid_courses) 
{
	vector <string> sorted = sort_alphabetically(valid_courses);
	for (int i = 0; i < sorted.size(); i++) 
    {
		for (int j = 0; j < valid_courses.size(); j++) 
        {
			if (sorted[i] == valid_courses[j].name) 
            {
				cout << valid_courses[j].ID << endl;
				break;
			}
		}
	}

}

vector<string> sort_alphabetically(CourseTable valid_courses) 
{
	vector <string> sorted;
	for (int i = 0; i < valid_courses.size(); i++) 
    {
		sorted.push_back(valid_courses[i].name);
	}
	sort(sorted.begin(), sorted.end());
	return sorted;
}