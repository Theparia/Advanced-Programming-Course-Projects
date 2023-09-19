#include <iostream>
#include <string>
#include <functional>
#include <cmath>
using namespace std;
unsigned long int generatePasswordHash(string password);
void CheckPassword(string valid_letters,string new_word,const int sizeof_valid_letters,const int size,unsigned long int hashed_password,long int &count,long int number_of_cases,int &result );
int main()
{
int size;
string valid_letters;
unsigned long int hashed_password;

cin>>size>>valid_letters>>hashed_password;
long int number_of_cases = pow((valid_letters).size(),size);
long int count=0;
int result=0;
CheckPassword(valid_letters,"",(valid_letters).size(),size,hashed_password,count,number_of_cases,result);
}

unsigned long int generatePasswordHash(string password)
{
    return hash<string>() (password);
}

void CheckPassword(string valid_letters,string new_word,const int sizeof_valid_letters,const  int size,unsigned long int hashed_password,long int &count,long int number_of_cases,int &result )
{
    if (size == 1)
    {
        for (int j = 0; j < sizeof_valid_letters; j++)
        {
            count++;
            if(generatePasswordHash(new_word + valid_letters[j])==hashed_password)
            {
                result=1;
                cout<< (new_word + valid_letters[j])<<endl;
                return;
            }

        }
        if(count == number_of_cases && result==0)
        {
            cout<< "NOT_FOUND"<<endl;
            return;
        }

    }
    else
    {
        for (int i = 0; i <sizeof_valid_letters; i++)
        {
            if(result)
            return;
            CheckPassword(valid_letters, new_word + valid_letters[i], sizeof_valid_letters, size - 1,hashed_password,count,number_of_cases,result);
        }

    }
}