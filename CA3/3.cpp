#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

#define TOP_STUDENT_MIN_GPA 17
#define TOP_STUDENT_MAX_UNITS 24
#define STUDENT_MAX_UNITS 20

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
    int units;
};
typedef vector <Course> CourseTable;
typedef vector <Grade> GradeTable;

CourseTable read_course_info(string address);
void insert_prerequisties_to_CourseTable(CourseTable &courses,string pre_courses,Course *new_course);
void insert_schedule_to_CourseTable(CourseTable &courses,string time_table,Course *new_course);
int string_to_int(string address);
float string_to_float(string input);
GradeTable read_grades(string address);
vector<string> sort_alphabetically(CourseTable valid_courses);
bool has_already_passed_course(Course x, GradeTable y);
bool has_passed_prequisite(Course x, GradeTable y,int index);
bool has_passed_all_prequisites(Course x, GradeTable y);
CourseTable find_takable_courses(CourseTable x, GradeTable y);
float calculate_gpa(CourseTable x,GradeTable y);
bool is_the_student_top(float gpa);
CourseTable sort_units(CourseTable valid_courses);
CourseTable sort_courses_with_same_units(CourseTable same_units);
bool has_overlap(CourseTable taken_courses,Time x);
int time_to_min(int h,int m);
CourseTable find_registered_courses(CourseTable x,GradeTable y,CourseTable valid_courses,float gpa);
void write_plan_in_file(CourseTable taken_courses,int number);
void generate_recommended_plan(CourseTable x,GradeTable y,int number,float gpa);

int main(int argc,char* argv[])
{
    CourseTable courses=read_course_info(argv[1]);
    GradeTable grades=read_grades(argv[2]);
    float gpa=calculate_gpa(courses,grades);
    generate_recommended_plan(courses,grades,1,gpa);
}

CourseTable read_course_info(string address) {
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
	for (int i = 0; i < courses.size(); i++) 
    {
		if (has_already_passed_course(courses[i], grades) == 0 && has_passed_all_prequisites(courses[i],grades) == 1)
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
		for (int i = 0; i <grades.size(); i++) 
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
float calculate_gpa(CourseTable courses,GradeTable grades)
{
    GradeTable temp;
    float sum=0;
    int num=0;
    for(int i=0;i<grades.size();i++)
    {

        for(int j=0;j<courses.size();j++)
        {
            if(grades[i].ID==courses[j].ID)
            {
                grades[i].units=courses[j].units;
                break;
            }
        }

    }
    
    for(int i=grades.size()-1;i>=0;i--)
    {
        int not_repeated=1;
        for(int j=0;j<temp.size();j++)
        {
            if(temp[j].ID==grades[i].ID)
            {
                not_repeated=0;
            }
        }
    if(not_repeated)
    {
        temp.push_back(grades[i]);
    }
    }
    for(int i=0;i<temp.size();i++)
    {
        sum+=(temp[i].grade)*(temp[i].units);
        num+=temp[i].units;
    }
    float gpa=sum/num;
    return gpa;

}
bool is_the_student_top(float gpa)
{
    if(gpa>=TOP_STUDENT_MIN_GPA)
    return true;
    return false;

}
CourseTable sort_units(CourseTable valid_courses)
{
    CourseTable sorted;
    CourseTable same_units;
	vector <int> temp;
	for (int i = 0; i < valid_courses.size(); i++) 
    {
		temp.push_back(valid_courses[i].units);
	}
	sort(temp.begin(), temp.end());
	reverse(temp.begin(),temp.end());
    int count=1;
    for(int i=0;i<temp.size();i++)
    {
        if(temp[i]!=temp[i+1])
        {
            for(int j=0;j<valid_courses.size();j++)
            {
                if(valid_courses[j].units==temp[i])
                    same_units.push_back(valid_courses[j]);
            }
            same_units = sort_courses_with_same_units(same_units);
            for(int j=0;j<count;j++)
            {
                sorted.push_back(same_units[j]);
            }
            same_units.clear();
            count=1;
        }
        
         else count++;
    }
    return sorted;
}
CourseTable sort_courses_with_same_units(CourseTable same_units){
    vector <string> temp=sort_alphabetically(same_units);
    CourseTable sorted;
    for(int j=0;j<temp.size();j++)
    {
        for(int i=0;i<same_units.size();i++)
        {
            if(same_units[i].name==temp[j]){
            sorted.push_back(same_units[i]);
            break;
            }

        }
        
    }
    return sorted;
}
bool has_overlap(CourseTable taken_courses,Time x)
{
    for(int i=0;i<taken_courses.size();i++)
    {
        for(int j=0;j<taken_courses[i].schedule.size();j++)
        {
            if(taken_courses[i].schedule[j].day==x.day)
            {
                if(time_to_min(x.start_hour,x.start_min)>=time_to_min(taken_courses[i].schedule[j].start_hour,taken_courses[i].schedule[j].start_min)
                && time_to_min(x.start_hour,x.start_min)<time_to_min(taken_courses[i].schedule[j].end_hour,taken_courses[i].schedule[j].end_min))
                {
                    return true;
                    break;
                }
                if(time_to_min(x.start_hour,x.start_min)<=time_to_min(taken_courses[i].schedule[j].start_hour,taken_courses[i].schedule[j].start_min)
                && time_to_min(x.end_hour,x.end_min)>time_to_min(taken_courses[i].schedule[j].start_hour,taken_courses[i].schedule[j].start_min))
                    {
                        return true;
                        break;
                    }
            }
        }
    }
    return false;
}
int time_to_min(int h,int m){
    if(h==0)
    h=24;
    return h*60 + m;
}
CourseTable find_registered_courses(CourseTable x,GradeTable y,CourseTable valid_courses,float gpa)
{   
    int number_of_units=0;
    CourseTable taken_courses;
    int max;
    int valid;
    if(is_the_student_top(gpa))
        max=TOP_STUDENT_MAX_UNITS;
    else 
        max=STUDENT_MAX_UNITS;

    for(int i=0;i<valid_courses.size();i++)
    {
        valid=1;
        if(number_of_units+valid_courses[i].units > max )
            valid=0;
        else
        {
            for(int j=0;j<valid_courses[i].schedule.size();j++)
            {
            if(has_overlap(taken_courses,valid_courses[i].schedule[j])==1)
               valid=0;
            }
        }
        if(valid )
        {
        taken_courses.push_back(valid_courses[i]);
        number_of_units+=valid_courses[i].units;
        }
    }

    return taken_courses;
}

void generate_recommended_plan(CourseTable courses,GradeTable grades,int number,float gpa)
{
    Grade *temp;
    CourseTable valid_courses=find_takable_courses(courses,grades);
    if(valid_courses.size()==0)
    return;
    CourseTable sorted=sort_units(valid_courses);
    CourseTable taken_courses=find_registered_courses(courses,grades,sorted,gpa);
    write_plan_in_file(taken_courses,number);
    for(int i=0;i<taken_courses.size();i++)
    {
       temp= new Grade;
       temp->ID=taken_courses[i].ID;
       temp->grade=15;
       grades.push_back(*temp);
       delete temp;
    }
    valid_courses.clear();
    sorted.clear();
    taken_courses.clear();
    gpa=(gpa+1.05*gpa)/2;
    generate_recommended_plan(courses,grades,number+1,gpa);
    
}

void write_plan_in_file(CourseTable taken_courses,int number)
{
    ofstream file;
    string address="semester";
    address+=to_string(number)+".sched";
    file.open(address);
	vector <string> sorted = sort_alphabetically(taken_courses);
	for (int i = 0; i < sorted.size(); i++) 
    {
		for (int j = 0; j < taken_courses.size(); j++) 
        {
			if (sorted[i] == taken_courses[j].name) 
            {
				file << taken_courses[j].ID << endl;
				break;
			}
		}
	}
    file.close();

}